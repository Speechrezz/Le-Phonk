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

    void checkForUpdates();
    void checkAsync();
    juce::String getVersionFromServer();

    void timerCallback() override;

    // Returns false if update needs to be checked
    bool checkProperties();

    // Called once this class determines whether or not there is an update
    std::function<void(bool)> updateCallback = [](bool) {};

    inline int getUpdateState() const { return updateAtomic.load(std::memory_order_relaxed); };
    inline juce::String getLatestVersion() const { return latestVersion; };

    enum UpdateStates { checkingUpdate = -1, noUpdate, updateAvailable };

private:
    // Returns true if there is a newer version
    bool versionComparison(juce::String& newestVersion);
    int converVersionToSum(juce::String version);

    xynth::GuiData& guiData;

    bool checked = false;

    std::future<void> checkServerFuture;
    std::atomic<int> updateAtomic = -1;

    juce::String latestVersion = "null";
    std::mutex updatesMutex;
};
}