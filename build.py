import os
import platform
import subprocess
import sys
import argparse
from pathlib import Path
from dataclasses import dataclass
from dotenv import load_dotenv
from typing import cast

VST3_KEY = "vst3"
AU_KEY = "au"
CLAP_KEY = "clap"

load_dotenv()


'''
---Compile/Build---
'''

@dataclass
class GeneratorType:
    is_multi_config: bool
    arguments: list[str]

def detect_generator():
    system = platform.system()
    if system == "Windows":
        return GeneratorType(is_multi_config=True, arguments=["-G", "Visual Studio 18 2026"])
    elif system == "Darwin": # MacOS
        # Use Ninja if available, otherwise default to Xcode
        if shutil.which("ninja"):
            return GeneratorType(is_multi_config=False, arguments=["-G", "Ninja"])
        else:
            return GeneratorType(is_multi_config=True, arguments=["-G", "Xcode"])
    else:
        return GeneratorType(is_multi_config=False, arguments=["-G", "Ninja"])
    
def compile(build_dir: str, build_type: str, is_demo=False, target: str | None=None):
    os.makedirs(build_dir, exist_ok=True)

    generator = detect_generator()

    # Configure (`cmake -B Builds`)
    configure_cmd = ["cmake", "-B", build_dir, *generator.arguments]
    if not generator.is_multi_config:
        configure_cmd += ["-DCMAKE_BUILD_TYPE=" + build_type]
    if is_demo:
        configure_cmd += ["-DBUILD_DEMO=ON"]

    print("Configuring...")
    subprocess.run(configure_cmd, check=True)

    # Build (`cmake --build Builds`)
    build_cmd = ["cmake", "--build", build_dir]
    if generator.is_multi_config:
        build_cmd += ["--config", build_type]
    if target:
        build_cmd += ["--target", target]

    print("Building...")
    subprocess.run(build_cmd, check=True)


'''
---Bundle---
'''

@dataclass
class BundleConfig:
    plugin_name: str
    plugin_version: str
    company_name: str
    output_path: Path
    manual_install_dir: Path
    installer_path: Path
    binary_paths: dict[str, Path]
    bundle_id: str = ""

binary_suffix_to_id = {
    "vst3": "vst3",
    "component": "au",
    "clap": "clap",
    "aax": "aax"
}

binary_id_to_install_folder = {
    "vst3": "VST3",
    "au": "Components",
    "clap": "CLAP",
    "aax": "AAX"
}

def bundle(build_dir: str, build_type: str, is_demo: bool = False):
    system = platform.system()
    if system == "Windows":
        bundle_windows(build_dir, build_type, is_demo)
    elif system == "Darwin": # MacOS
        bundle_macos(build_dir, build_type, is_demo)
    else:
        pass

def get_binary_path(folder: str, extension: str, build_dir: str, build_type: str):
    artifacts_dir_list = list(Path(build_dir).glob(f"*artefacts/{build_type}/{folder}/*{extension}"))
    if not artifacts_dir_list:
        raise FileNotFoundError(f"Could not find {extension} binary.")
    
    return artifacts_dir_list[0]

def get_project_version(build_dir: str):
    cache = Path(build_dir) / "CMakeCache.txt"
    for line in cache.read_text().splitlines():
        if line.startswith("CMAKE_PROJECT_VERSION:"):
            return line.split("=", 1)[1]
    raise ValueError("CMAKE_PROJECT_VERSION not found")

def get_bundle_config_windows(build_dir: str, build_type: str, is_demo: bool, installer_dir=Path("Installers/Windows")):
    plugin_name = cast(str, os.getenv("PLUGIN_NAME"))
    company_name = cast(str, os.getenv("COMPANY_NAME"))
    if is_demo:
        plugin_name += " DEMO"

    binary_paths = {
        VST3_KEY: get_binary_path("VST3", ".vst3", build_dir, build_type),
        CLAP_KEY: get_binary_path("CLAP", ".clap", build_dir, build_type)
    }

    return BundleConfig(
        plugin_name = plugin_name,
        company_name = company_name,
        plugin_version = get_project_version(build_dir),
        output_path = installer_dir / f"{plugin_name} (Windows).zip",
        manual_install_dir = installer_dir / "Manual Install",
        installer_path = installer_dir / f"{plugin_name} Installer.exe",
        binary_paths = binary_paths
    )

def bundle_windows(build_dir: str, build_type: str, is_demo: bool):
    SIGNTOOL_PATH = Path(cast(str, os.getenv("SIGNTOOL_PATH")))
    ISCC_PATH = Path(cast(str, os.getenv("ISCC_PATH")))
    SEVEN_ZIP_PATH = Path(cast(str, os.getenv("SEVEN_ZIP_PATH")))
    AZURE_DLIB_PATH = Path(cast(str, os.getenv("AZURE_DLIB_PATH")))

    config = get_bundle_config_windows(build_dir, build_type, is_demo)

    # 1. Prepare Manual Install directory
    print(f"Copying {config.plugin_name} to Manual Install directory")

    config.manual_install_dir.mkdir(parents=True, exist_ok=True)
    for path in config.binary_paths.values():
        if (path.is_dir()):
            shutil.copytree(path, config.manual_install_dir / path.name)
        else:
            shutil.copy(path, config.manual_install_dir / path.name)
    shutil.copy("Installers/Common/Manual Install Instructions.txt", config.manual_install_dir)

    # 2. Compile installer
    print("\nCompiling installer...")
    installer_output_name = config.installer_path.stem
    project_version = get_project_version(build_dir)
    subprocess.run([
        ISCC_PATH, 
        f"/DMyAppName={config.binary_paths[VST3_KEY].stem}", 
        f"/DMyOutputName={installer_output_name}", 
        f"/DMyAppVersion={project_version}", 
        "Installers/Windows/installer.iss"
    ], check=True)

    # 3. Sign installer
    print("\nSigning installer...")
    subprocess.run([
        SIGNTOOL_PATH,
        "sign",
        "-v", "-debug",
        "-fd", "SHA256",
        "-tr", "http://timestamp.acs.microsoft.com",
        "-td", "SHA256",
        "-dlib", AZURE_DLIB_PATH,
        "-dmdf", ".\Installers\Windows\metadata.json",
        config.installer_path
    ], check=True)

    # 4. Verify signature
    print("\nVerifying signature...")
    verify_result = subprocess.run([
        SIGNTOOL_PATH,
        "verify",
        "-pa",
        str(config.installer_path)
    ], capture_output=True, text=True)

    # 5. Create zip archive
    print(f"\nCreating final {config.output_path.name}...")
    current_working_dir = os.getcwd()
    os.chdir(config.installer_path.parent)
    # subprocess.run([SEVEN_ZIP_PATH, "a", config.output_path.name, config.manual_install_dir.name], check=True)
    subprocess.run([SEVEN_ZIP_PATH, "a", config.output_path.name, config.installer_path.name], check=True)
    os.chdir(current_working_dir)

    # 6. Clean up
    print("\nCleaning up...")
    shutil.rmtree(config.manual_install_dir)
    config.installer_path.unlink(missing_ok=True)

    # 7. Print results
    print(verify_result.stdout, end="")
    if verify_result.returncode != 0:
        print("❌ Signature verification failed!")
        print(verify_result.stderr)
        raise RuntimeError("Signature verification failed.")
    

def get_bundle_config_macos(build_dir: str, build_type: str, is_demo: bool, installer_dir=Path("Installers/MacOS")):
    plugin_name = cast(str, os.getenv("PLUGIN_NAME"))
    company_name = cast(str, os.getenv("COMPANY_NAME"))
    bundle_id = f"com.{company_name.replace(' ', '')}.{plugin_name.replace(' ', '')}"

    if is_demo:
        plugin_name += " DEMO"

    binary_paths = {
        VST3_KEY: get_binary_path("VST3", ".vst3", build_dir, build_type),
        CLAP_KEY: get_binary_path("CLAP", ".clap", build_dir, build_type),
        AU_KEY: get_binary_path("AU", ".component", build_dir, build_type)
    }

    return BundleConfig(
        plugin_name = plugin_name,
        company_name = company_name,
        plugin_version = get_project_version(build_dir),
        bundle_id = bundle_id,
        output_path = installer_dir / f"{plugin_name} (MacOS).zip",
        manual_install_dir = installer_dir / "Manual Install",
        installer_path = installer_dir / f"{plugin_name} Installer.pkg",
        binary_paths = binary_paths
    )

def sign_and_notarize_plugin_macos(plugin_path: Path, output_path: Path):
    print(f"\n🔏 Signing and notarizing: {plugin_path.name}")

    DEVELOPER_NAME = cast(str, os.getenv("DEVELOPER_NAME"))
    APPLE_ID = cast(str, os.getenv("APPLE_ID"))
    TEAM_ID = cast(str, os.getenv("TEAM_ID"))
    SIGNING_PASSWORD = cast(str, os.getenv("SIGNING_PASSWORD"))

    # Step 1: codesign
    subprocess.run([
        "codesign", "-s", f"Developer ID Application: {DEVELOPER_NAME} ({TEAM_ID})",
        "-vvvv", "--force", "--deep", "--timestamp",
        "-o", "runtime",
        str(plugin_path)
    ], check=True)

    # Step 2: zip for notarization (must use `ditto`)
    zip_path = Path("Plugin.zip")
    subprocess.run([
        "ditto", "-c", "-k", "--sequesterRsrc", "--keepParent",
        str(plugin_path),
        str(zip_path)
    ], check=True)

    # Step 3: submit for notarization
    subprocess.run([
        "xcrun", "notarytool", "submit", str(zip_path),
        "--apple-id", APPLE_ID,
        "--password", SIGNING_PASSWORD,
        "--team-id", TEAM_ID,
        "--wait"
    ], check=True)
    zip_path.unlink()

    # Step 4: staple
    subprocess.run(["xcrun", "stapler", "staple", str(plugin_path)], check=True)

    # Step 5: Copy to Manual Install
    output_path.mkdir(parents=True, exist_ok=True)
    shutil.copytree(plugin_path, output_path / plugin_path.name)

def build_installer_macos(config: BundleConfig):
    packaging_dir = config.installer_path.parent / "Packaging"
    packaging_dir.mkdir(parents=True, exist_ok=True)

    choice_outline: list[str] = []
    choice_list: list[str] = []

    # Create sub packages for each binary
    for binary_path in config.manual_install_dir.iterdir():
        if binary_path.suffix == "": # Skip .DS_Store and stuff
            continue

        suffix = binary_path.suffix.replace(".", "")
        binary_id = binary_suffix_to_id[suffix]
        identifier = f"{config.bundle_id}.{binary_id}.pkg"
        pkg_file = packaging_dir / f"{config.company_name.replace(' ', '')}.{binary_id}.pkg"

        choice_outline.append(f'\t\t<line choice="{binary_id}" />')
        choice_list.append(
            f'\t<choice id="{binary_id}" visible="true" start_selected="true" title="{config.plugin_name} {binary_id}">\n'
            f'\t\t<pkg-ref id="{identifier}" version="{config.plugin_version}" onConclusion="none">{pkg_file.name}</pkg-ref>\n'
            '\t</choice>'
        )

        subprocess.run([
            "pkgbuild",
            "--identifier", identifier,
            "--version", config.plugin_version,
            "--component", binary_path,
            "--install-location", f"/Library/Audio/Plug-Ins/{binary_id_to_install_folder[binary_id]}",
            pkg_file
        ], check=True)

    # Create distribution.xml file
    choice_outline_str = "\n".join(choice_outline)
    choice_list_str = "\n\n".join(choice_list)

    distribution_xml = f'''<?xml version="1.0" encoding="utf-8"?>
<installer-gui-script minSpecVersion="2">
    <title>{config.plugin_name}</title>
    <allowed-os-versions>
        <os-version min="10.13" />
    </allowed-os-versions>
    <license file="License.rtf" />
    <readme file="Before Install.rtf" />

    <choices-outline>
{choice_outline_str}
    </choices-outline>

{choice_list_str}
</installer-gui-script>'''

    distribution_xml_path = packaging_dir / "distribution.xml"
    with open(distribution_xml_path, 'w') as file:
        file.write(distribution_xml)

    # Create the final .pkg installer
    subprocess.run([
        "productbuild",
        "--resources", "Installers/Common",
        "--package-path", packaging_dir,
        "--distribution", distribution_xml_path,
        config.installer_path
    ], check=True)

    # Clean up
    shutil.rmtree(packaging_dir)

def bundle_macos(build_dir: str, build_type: str, is_demo: bool):
    DEVELOPER_NAME = cast(str, os.getenv("DEVELOPER_NAME"))
    APPLE_ID = cast(str, os.getenv("APPLE_ID"))
    TEAM_ID = cast(str, os.getenv("TEAM_ID"))
    SIGNING_PASSWORD = cast(str, os.getenv("SIGNING_PASSWORD"))

    config = get_bundle_config_macos(build_dir, build_type, is_demo)

    print(f"Bundling and signing {config.plugin_name}")

    # Step 1: Sign and notarize .vst3 and .component
    for path in config.binary_paths.values():
        sign_and_notarize_plugin_macos(path, config.manual_install_dir)

    # Step 2: Build installer
    print("\n📦 Building installer...")
    build_installer_macos(config)

    # Step 3: Productsign the installer
    print("\n🔏 Signing installer...")
    signed_installer_path = config.installer_path.parent / ("Signed " + config.installer_path.name)
    subprocess.run([
        "productsign",
        "-s", f"Developer ID Installer: {DEVELOPER_NAME} ({TEAM_ID})",
        str(config.installer_path),
        str(signed_installer_path)
    ], check=True)
    shutil.move(str(signed_installer_path), str(config.installer_path))

    # Step 4: Notarize installer
    print("\n🛡️ Notarizing installer...")
    subprocess.run([
        "xcrun", "notarytool", "submit", str(config.installer_path),
        "--apple-id", APPLE_ID,
        "--password", SIGNING_PASSWORD,
        "--team-id", TEAM_ID,
        "--wait"
    ], check=True)
    subprocess.run(["xcrun", "stapler", "staple", str(config.installer_path)], check=True)

    # Step 5: Create .zip with installer and manual install files
    print("\n📦 Archiving final installer...")
    shutil.copy("Installers/Common/Manual Install Instructions.txt", config.manual_install_dir)

    current_working_dir = os.getcwd()
    os.chdir(config.installer_path.parent)
    subprocess.run(["zip", "-r", config.output_path.name, config.manual_install_dir.name], check=True)
    subprocess.run(["zip", config.output_path.name, config.installer_path.name], check=True)
    os.chdir(current_working_dir)

    # Step 6: Clean up
    print("\n🧹 Cleaning up...")
    shutil.rmtree(config.manual_install_dir)
    config.installer_path.unlink()

    print("\n✅ Done!")


if __name__ == "__main__":
    import shutil

    parser = argparse.ArgumentParser(description="Cross-platform CMake build script.")
    parser.add_argument("--build-dir", default="Builds", help="Build directory")
    parser.add_argument("--build-dir-demo", default="Builds/Demo", help="Build directory for demo")
    parser.add_argument("--build-type", default="Release", help="Build type (Debug, Release, etc.)")

    parser.add_argument("--target", help="Specific target to build")

    parser.add_argument("--include-demo", action='store_true', help="Include to also build & bundle the demo version")

    parser.add_argument("--skip-compile", action='store_true', help="Include to skip the compile step")
    parser.add_argument("--skip-bundle", action='store_true', help="Include to skip the bundle step")

    args = parser.parse_args()

    if not args.skip_compile:
        try:
            compile(args.build_dir, args.build_type, args.target)
            if args.include_demo:
                compile(args.build_dir_demo, args.build_type, is_demo=True, target=args.target)
        except subprocess.CalledProcessError:
            sys.exit("❌ Build failed.")

    if not args.skip_bundle:
        try:
            bundle(args.build_dir, args.build_type)
            if args.include_demo:
                bundle(args.build_dir_demo, args.build_type, is_demo=True)
        except subprocess.CalledProcessError:
            sys.exit("❌ Bundle failed.")