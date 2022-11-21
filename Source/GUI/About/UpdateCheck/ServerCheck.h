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
class ServerCheck : public juce::Timer
{
public:
    ServerCheck(xynth::GuiData&);
    ~ServerCheck() = default;

    void checkForUpdates();
    void checkAsync();
    juce::String getVersionFromServer();

    void timerCallback() override;

    // Called once this class determines whether or not there is an update
    std::function<void(bool)> updateCallback = [](bool) {};

private:
    // Returns true if there is a newer version
    bool versionComparison(juce::String& newestVersion);
    int converVersionToSum(juce::String version);

    xynth::GuiData& guiData;

    bool checked = false;

    std::future<void> checkServerFuture;
    std::atomic<int> updateAtomic = -1;

};
}