/*
  ==============================================================================

    UpdateChecker.cpp
    Created: 20 Nov 2022 6:15:37pm
    Author:  thesp

  ==============================================================================
*/

#include "UpdateChecker.h"

#define UPDATE_CHECKED_TIME_ID ""
#define NOTIFY_UPDATES_ID "NotifyUpdates"

namespace xynth
{
UpdateChecker::UpdateChecker(xynth::GuiData& g) : guiData(g)
{}

void UpdateChecker::checkForUpdates()
{
    // Check if user wants to check for updates

    updateState = checkingUpdate;

    startTimerHz(20);
    checkServerFuture = std::async(std::launch::async, [this]() {checkAsync(); });
}

void UpdateChecker::checkAsync()
{
    // Retrieve newest version from server
    juce::String version = getVersionFromServer();
    DBG("[UPDATE CHECK] Newest version: " << version);

    if (version == "Error")
    {
        std::lock_guard<std::mutex> lock(updatesMutex);
        updateState = updateError;
    }
    else
    {
        // Check if update is available
        const bool isUpdateAvailable = versionComparison(version);
        std::lock_guard<std::mutex> lock(updatesMutex);
        updateState = (UpdateStates)isUpdateAvailable;
    }
}

juce::String UpdateChecker::getVersionFromServer()
{
    juce::StringPairArray responseHeaders;
    int statusCode = 0;

    auto url = juce::URL("https://www.xynthaudio.com/plugins/lephonk/info");

    if (auto stream = url
        .createInputStream(juce::URL::InputStreamOptions(juce::URL::ParameterHandling::inAddress)
            .withConnectionTimeoutMs(2000)
            .withResponseHeaders(&responseHeaders)
            .withStatusCode(&statusCode)))
    {
        if (statusCode == 200)
        {
            auto resultJSON = juce::JSON::fromString(stream->readEntireStreamAsString());
            const auto& version = resultJSON["version"];

            DBG("[UPDATE CHECK] Successful connection, status code = " + juce::String(statusCode));
            if (version.isString())
            {
                std::lock_guard<std::mutex> lock(updatesMutex);
                latestVersion = version;
                return version;
            }
            else
            {
                DBG("[UPDATE CHECK] Error reading JSON");
                std::lock_guard<std::mutex> lock(updatesMutex);
                latestVersion = juce::String(statusCode) + " - JSON error";
                return "Error";
            }
        }
    }

    DBG("[UPDATE CHECK] FAILED to connect, status code = " + juce::String(statusCode));
    std::lock_guard<std::mutex> lock(updatesMutex);
    latestVersion = juce::String(statusCode);
    return "Error";
}

bool UpdateChecker::versionComparison(juce::String& newestVersion)
{
    const int currentSum = converVersionToSum(JucePlugin_VersionString);
    const int newestSum  = converVersionToSum(newestVersion);

    return newestSum > currentSum;
}

int UpdateChecker::converVersionToSum(juce::String version)
{
    int weight = 1;
    int sum = 0;
    juce::String num = "";

    for (int i = version.length() - 1; i >= 0; --i)
    {
        if (version[i] == '.')
        {
            sum += num.getIntValue() * weight;

            num = "";
            weight *= 1000;
        }
        else
        {
            num = version[i] + num;
        }
    }
    sum += num.getIntValue() * weight;

    return sum;
}

void UpdateChecker::timerCallback()
{
    // Checks for async to finish
    if (updateState != -1)
    {
        stopTimer();
        DBG("updateState: " << updateState);
        updateCallback(updateState == updateAvailable);
    }
}

void UpdateChecker::setNotifyUpdatesSetting(const bool newSetting)
{
    auto* properties = guiData.properties.getUserSettings();
    properties->setValue(NOTIFY_UPDATES_ID, newSetting);
    properties->saveIfNeeded();
}

bool UpdateChecker::getNotifyUpdatesSetting() const
{
    auto* properties = guiData.properties.getUserSettings();
    return properties->getBoolValue(NOTIFY_UPDATES_ID);
}
}