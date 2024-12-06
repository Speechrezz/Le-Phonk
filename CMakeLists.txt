# Example Audio Plugin CMakeLists.txt

# To get started on a new plugin, copy this entire folder (containing this file and C++ sources) to
# a convenient location, and then start making modifications.

# The first line of any CMake project should be a call to `cmake_minimum_required`, which checks
# that the installed CMake will be able to understand the following CMakeLists, and ensures that
# CMake's behaviour is compatible with the named version. This is a standard CMake command, so more
# information can be found in the CMake docs.

cmake_minimum_required(VERSION 3.15)

if (APPLE)
  # Make the fat binary
  set(CMAKE_OSX_ARCHITECTURES "arm64;x86_64" CACHE STRING "" FORCE)
endif()

# The top-level CMakeLists.txt file for a project must contain a literal, direct call to the
# `project()` command. `project()` sets up some helpful variables that describe source/binary
# directories, and the current project version. This is a standard CMake command.

project(LePhonk VERSION 1.0.4)

# If you've installed JUCE somehow (via a package manager, or directly using the CMake install
# target), you'll need to tell this project that it depends on the installed copy of JUCE. If you've
# included JUCE directly in your source tree (perhaps as a submodule), you'll need to tell CMake to
# include that subdirectory as part of the build.

# find_package(JUCE CONFIG REQUIRED)        # If you've installed JUCE to your system
# or
add_subdirectory(JUCE)                    # If you've put JUCE in a subdirectory called JUCE

# Statically link C++ Runtime library on Windows. Dynamically linking means we have to rely on the
# runtime library installed on the users computer. If the user has an outdated version of this library
# crashed occur.
if (MSVC)
  set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()

# If you are building a VST2 or AAX plugin, CMake needs to be told where to find these SDKs on your
# system. This setup should be done before calling `juce_add_plugin`.

# juce_set_vst2_sdk_path(...)
# juce_set_aax_sdk_path(...)

# `juce_add_plugin` adds a static library target with the name passed as the first argument
# (LePhonk here). This target is a normal CMake target, but has a lot of extra properties set
# up by default. As well as this shared code static library, this function adds targets for each of
# the formats specified by the FORMATS arguments. This function accepts many optional arguments.
# Check the readme at `docs/CMake API.md` in the JUCE repo for the full list.

juce_add_plugin(LePhonk
    VERSION 1.0.4                               # Set this if the plugin version is different to the project version
    # ICON_BIG ...                              # ICON_* arguments specify a path to an image file to use as an icon for the Standalone
    # ICON_SMALL ...
    COMPANY_NAME "Xynth Audio"                  # Specify the name of the plugin's author
    IS_SYNTH FALSE                              # Is this a synth or an effect?
    NEEDS_MIDI_INPUT FALSE                      # Does the plugin need midi input?
    NEEDS_MIDI_OUTPUT FALSE                     # Does the plugin need midi output?
    IS_MIDI_EFFECT FALSE                        # Is this plugin a MIDI effect?
    EDITOR_WANTS_KEYBOARD_FOCUS FALSE           # Does the editor need keyboard focus?
    # COPY_PLUGIN_AFTER_BUILD TRUE/FALSE        # Should the plugin be installed to a default location after building?
    PLUGIN_MANUFACTURER_CODE Manu               # A four-character manufacturer id with at least one upper-case character
    PLUGIN_CODE Hrzu                            # A unique four-character plugin id with exactly one upper-case character
                                                # GarageBand 10.3 requires the first letter to be upper-case, and the remaining letters to be lower-case
    FORMATS AU VST3 Standalone                  # The formats to build. Other valid formats are: AAX Unity VST AU AUv3
    VST3_CATEGORIES Fx Distortion Dynamics 
    AU_MAIN_TYPE kAudioUnitType_Effect
    PRODUCT_NAME "LePhonk")                     # The name of the final executable, which can differ from the target name

# `juce_generate_juce_header` will create a JuceHeader.h for a given target, which will be generated
# into your build tree. This should be included with `#include <JuceHeader.h>`. The include path for
# this header will be automatically added to the target. The main function of the JuceHeader is to
# include all your JUCE module headers; if you're happy to include module headers directly, you
# probably don't need to call this.

juce_generate_juce_header(LePhonk)

# Create source file GLOB

file(GLOB MY_SOURCES
    Res/Drippy/au5Knob.png
    Res/Drippy/danBG.png
    Res/Drippy/danKnob.png
    Res/Drippy/eliKnob.png
    Res/Drippy/exylKnob.png
    Res/Drippy/peteKnob.png
    Res/Drippy/sharkKnob.png
    Res/Drippy/skyKnob.png
    Res/Drippy/speechKnob.png
    Res/Fonts/Montserrat-Regular.ttf
    Res/Fonts/MuseoModerno-Bold.ttf
    Res/Fonts/MuseoModerno-Light.ttf
    Res/Fonts/MuseoModerno-Medium.ttf
    Res/Fonts/MuseoModerno-Regular.ttf
    Res/Fonts/MuseoModerno-SemiBold.ttf
    Res/Fonts/MuseoModerno-Thin.ttf
    Res/backArrow.svg
    Res/drippyBG.png
    Res/hellBG.png
    Res/juiceBG.png
    Res/xynthLogo.png
    Source/Common/Constants.h
    Source/Common/ParameterText.cpp
    Source/Common/ParameterText.h
    Source/Common/Ranges.cpp
    Source/Common/Ranges.h
    Source/Common/RingBuffer.cpp
    Source/Common/RingBuffer.h
    Source/DSP/OTT/OTT.cpp
    Source/DSP/OTT/OTT.h
    Source/DSP/OTT/OTTwithMultiplier.cpp
    Source/DSP/OTT/OTTwithMultiplier.h
    Source/DSP/OTT/UpDownComp.cpp
    Source/DSP/OTT/UpDownComp.h
    Source/DSP/Utils/InterleavedAudio.cpp
    Source/DSP/Utils/InterleavedAudio.h
    Source/DSP/Utils/SIMDFilter.cpp
    Source/DSP/Utils/SIMDFilter.h
    Source/DSP/Zekete/Dist1.cpp
    Source/DSP/Zekete/Dist1.h
    Source/DSP/Zekete/Dist2.cpp
    Source/DSP/Zekete/Dist2.h
    Source/DSP/Zekete/Dist3.cpp
    Source/DSP/Zekete/Dist3.h
    Source/DSP/Zekete/Dist4.cpp
    Source/DSP/Zekete/Dist4.h
    Source/DSP/Zekete/Dist5.cpp
    Source/DSP/Zekete/Dist5.h
    Source/DSP/Zekete/Dist6.cpp
    Source/DSP/Zekete/Dist6.h
    Source/DSP/Zekete/DistTemplate.h
    Source/DSP/Zekete/ZeketeHeader.h
    Source/DSP/Fonz.cpp
    Source/DSP/Fonz.h
    Source/DSP/Zekete.cpp
    Source/DSP/Zekete.h
    Source/GUI/About/UpdateCheck/BackButton.cpp
    Source/GUI/About/UpdateCheck/BackButton.h
    Source/GUI/About/UpdateCheck/UpdateChecker.cpp
    Source/GUI/About/UpdateCheck/UpdateChecker.h
    Source/GUI/About/AboutOverlay.cpp
    Source/GUI/About/AboutOverlay.h
    Source/GUI/About/AboutWindow.cpp
    Source/GUI/About/AboutWindow.h
    Source/GUI/About/CheckmarkButton.cpp
    Source/GUI/About/CheckmarkButton.h
    Source/GUI/About/TextButton.cpp
    Source/GUI/About/TextButton.h
    Source/GUI/CustomLooks/CustomLook.cpp
    Source/GUI/CustomLooks/CustomLook.h
    Source/GUI/CustomLooks/DrippyLook.cpp
    Source/GUI/CustomLooks/DrippyLook.h
    Source/GUI/CustomLooks/HellLook.cpp
    Source/GUI/CustomLooks/HellLook.h
    Source/GUI/CustomLooks/JuiceLook.cpp
    Source/GUI/CustomLooks/JuiceLook.h
    Source/GUI/Fonz/FonzLayout.cpp
    Source/GUI/Fonz/FonzLayout.h
    Source/GUI/Header/BypassButton.cpp
    Source/GUI/Header/BypassButton.h
    Source/GUI/Header/BypassGain.cpp
    Source/GUI/Header/BypassGain.h
    Source/GUI/Header/LogoButton.cpp
    Source/GUI/Header/LogoButton.h
    Source/GUI/Header/SkinSelect.cpp
    Source/GUI/Header/SkinSelect.h
    Source/GUI/Ottz/MultiplierSlider.cpp
    Source/GUI/Ottz/MultiplierSlider.h
    Source/GUI/Ottz/OttzLayout.cpp
    Source/GUI/Ottz/OttzLayout.h
    Source/GUI/Ottz/TimeKnob.cpp
    Source/GUI/Ottz/TimeKnob.h
    Source/GUI/Utils/DualLabel.cpp
    Source/GUI/Utils/DualLabel.h
    Source/GUI/Utils/FullSlider.cpp
    Source/GUI/Utils/FullSlider.h
    Source/GUI/Utils/GuiData.h
    Source/GUI/Utils/TooltipLabel.cpp
    Source/GUI/Utils/TooltipLabel.h
    Source/GUI/Utils/TooltipSlider.cpp
    Source/GUI/Utils/TooltipSlider.h
    Source/GUI/Zekete/DistGraph.cpp
    Source/GUI/Zekete/DistGraph.h
    Source/GUI/Zekete/DistSelect.cpp
    Source/GUI/Zekete/DistSelect.h
    Source/GUI/Zekete/ZeketeLayout.cpp
    Source/GUI/Zekete/ZeketeLayout.h
    Source/GUI/WindowLayout.cpp
    Source/GUI/WindowLayout.h
    Source/PluginProcessor.cpp
    Source/PluginProcessor.h
    Source/PluginEditor.cpp
    Source/PluginEditor.h)

# Maintain folder structure

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${MY_SOURCES})

# `target_sources` adds source files to a target. We pass the target that needs the sources as the
# first argument, then a visibility parameter for the sources which should normally be PRIVATE.
# Finally, we supply a list of source files that will be built into the target. This is a standard
# CMake command.

target_sources(LePhonk
    PRIVATE ${MY_SOURCES})

# `target_compile_definitions` adds some preprocessor definitions to our target. In a Projucer
# project, these might be passed in the 'Preprocessor Definitions' field. JUCE modules also make use
# of compile definitions to switch certain features on/off, so if there's a particular feature you
# need that's not on by default, check the module header for the correct flag to set here. These
# definitions will be visible both to your code, and also the JUCE module code, so for new
# definitions, pick unique names that are unlikely to collide! This is a standard CMake command.

target_compile_definitions(LePhonk
    PUBLIC
        # JUCE_WEB_BROWSER and JUCE_USE_CURL would be on by default, but you might not need them.
        JUCE_WEB_BROWSER=0  # If you remove this, add `NEEDS_WEB_BROWSER TRUE` to the `juce_add_plugin` call
        JUCE_USE_CURL=0     # If you remove this, add `NEEDS_CURL TRUE` to the `juce_add_plugin` call
        JUCE_VST3_CAN_REPLACE_VST2=0
        JUCE_DISPLAY_SPLASH_SCREEN=0
        DONT_SET_USING_JUCE_NAMESPACE=1)

# If your target needs extra binary assets, you can add them here. The first argument is the name of
# a new static library target that will include all the binary resources. There is an optional
# `NAMESPACE` argument that can specify the namespace of the generated binary data class. Finally,
# the SOURCES argument should be followed by a list of source files that should be built into the
# static library. These source files can be of any kind (wav data, images, fonts, icons etc.).
# Conversion to binary-data will happen when your target is built.

juce_add_binary_data(AudioPluginData BinaryData SOURCES 
    Res/Drippy/au5Knob.png
    Res/Drippy/danBG.png
    Res/Drippy/danKnob.png
    Res/Drippy/eliKnob.png
    Res/Drippy/exylKnob.png
    Res/Drippy/peteKnob.png
    Res/Drippy/sharkKnob.png
    Res/Drippy/skyKnob.png
    Res/Drippy/speechKnob.png
    Res/Fonts/Montserrat-Regular.ttf
    Res/Fonts/MuseoModerno-Bold.ttf
    Res/Fonts/MuseoModerno-Light.ttf
    Res/Fonts/MuseoModerno-Medium.ttf
    Res/Fonts/MuseoModerno-Regular.ttf
    Res/Fonts/MuseoModerno-SemiBold.ttf
    Res/Fonts/MuseoModerno-Thin.ttf
    Res/backArrow.svg
    Res/drippyBG.png
    Res/hellBG.png
    Res/juiceBG.png
    Res/xynthLogo.png)

# `target_link_libraries` links libraries and JUCE modules to other libraries or executables. Here,
# we're linking our executable target to the `juce::juce_audio_utils` module. Inter-module
# dependencies are resolved automatically, so `juce_core`, `juce_events` and so on will also be
# linked automatically. If we'd generated a binary data target above, we would need to link to it
# here too. This is a standard CMake command.

target_link_libraries(LePhonk
    PRIVATE
        AudioPluginData           # If we'd created a binary data target, we'd link to it here
        juce::juce_audio_utils
        juce::juce_dsp
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags)
