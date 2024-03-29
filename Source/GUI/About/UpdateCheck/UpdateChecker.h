/*
  ==============================================================================

    ServerCheck.h
    Created: 20 Nov 2022 6:15:37pm
    Author:  thesp

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "../../Utils/GuiData.h"
#include <future>

namespace xynth
{
class UpdateChecker : public juce::Timer
{
public:
    UpdateChecker(xynth::GuiData&);
    ~UpdateChecker() = default;

    void startupUpdateCheck();
    void checkForUpdates();
    void checkAsync();
    juce::String getVersionFromServer();

    void timerCallback() override;

    // Called once this class determines whether or not there is an update.
    // Input parameter (bool): false if there is NO update, true if there IS.
    std::function<void(bool)> updateCallback = [](bool) {};

    inline int getUpdateState() const { return updateState; };
    inline juce::String getLatestVersion() const { return latestVersion; };

    void setNotifyUpdatesSetting(const bool newSetting);
    // Returns true if user does NOT want to be notified for updates
    // (checkmark is ticked)
    bool getNotifyUpdatesSetting() const;

    juce::int64 getLastUpdateTime() const;
    void setLastUpdateTime(const juce::int64 newTime);
    // Returns true if update needs to be checked
    bool checkLastUpdateTime();

    enum UpdateStates { invalidState = -1, noUpdateAvailable, updateAvailable, checkingUpdate, updateError };

private:
    // Returns true if there is a newer version
    bool versionComparison(juce::String& newestVersion);
    int converVersionToSum(juce::String version);

    xynth::GuiData& guiData;

    std::future<void> checkServerFuture;
    UpdateStates updateState = invalidState;

    juce::String latestVersion = "null";
    std::mutex updatesMutex;

    bool startupHasBeenChecked = true;
};
}