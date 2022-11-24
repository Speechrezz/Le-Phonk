/*
  ==============================================================================

    ServerCheck.cpp
    Created: 20 Nov 2022 6:15:37pm
    Author:  thesp

  ==============================================================================
*/

#include "ServerCheck.h"

#define UPDATE_CHECKED_TIME_ID ""
#define DO_NOT_REMIND_ME_ID "DoNotRemindMe"

namespace xynth
{
ServerCheck::ServerCheck(xynth::GuiData& g) : guiData(g)
{}

void ServerCheck::checkForUpdates()
{
    if (checked) return;
    checked = true;

    // Check if user wants to check for updates
    if (checkProperties())
        return;

    startTimerHz(20);
    checkServerFuture = std::async(std::launch::async, [this]() {checkAsync(); });
}

void ServerCheck::checkAsync()
{
    // Retrieve newest version from server
    juce::String version = getVersionFromServer();
    DBG("[UPDATE CHECK] Newest version: " << version);

    // Check if update is available
    const bool updateAvailable = versionComparison(version);
    updateAtomic.store((int)updateAvailable, std::memory_order_relaxed);
}

juce::String ServerCheck::getVersionFromServer()
{
    juce::StringPairArray responseHeaders;
    int statusCode = 0;

    auto url = juce::URL("https://www.xynthaudio.com/plugins/lephonk/info");

    if (auto stream = url
        .createInputStream(juce::URL::InputStreamOptions(juce::URL::ParameterHandling::inAddress)
            .withConnectionTimeoutMs(10000)
            .withResponseHeaders(&responseHeaders)
            .withStatusCode(&statusCode)))
    {
        if (statusCode != 0)
        {
            auto resultJSON = juce::JSON::fromString(stream->readEntireStreamAsString());
            const auto version = resultJSON["version"];

            DBG("[UPDATE CHECK] Successful connection, status code = " + juce::String(statusCode));
            if (version.isString())
                return version;
        }
    }

    DBG("[UPDATE CHECK] Failed to connect, status code = " + juce::String(statusCode));
    return "";
}

bool ServerCheck::versionComparison(juce::String& newestVersion)
{
    const int currentSum = converVersionToSum(JucePlugin_VersionString);
    const int newestSum  = converVersionToSum(newestVersion);

    return newestSum > currentSum;
}

int ServerCheck::converVersionToSum(juce::String version)
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

void ServerCheck::timerCallback()
{
    // Checks for async to finish
    const int value = updateAtomic.load(std::memory_order_relaxed);
    if (value != -1)
    {
        stopTimer();
        DBG("updateAtomic: " << value);
        updateCallback((bool)value);
    }
}
bool ServerCheck::checkProperties()
{
    auto* properties = guiData.properties.getUserSettings();

    return properties->getBoolValue(DO_NOT_REMIND_ME_ID, false);
}
}