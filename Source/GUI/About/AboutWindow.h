/*
  ==============================================================================

    AboutWindow.h
    Created: 8 Sep 2022 5:08:23pm
    Author:  thesp

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../Utils/GuiData.h"
#include "UpdateCheck/BackButton.h"
#include "UpdateCheck/UpdateChecker.h"
#include "TextButton.h"
#include "CheckmarkButton.h"

class AboutWindow  : public juce::Component
{
public:
    AboutWindow(xynth::GuiData&);

    void paint(juce::Graphics&) override;
    void resized() override;

    enum StatesEnum{ main, updates };
    void setState(const StatesEnum newState);

private:
    void initPaintFunctions();

    void initialized();
    bool isInitialized = false;

    typedef std::function<void(juce::Graphics& g, juce::Rectangle<float>& rect, juce::CustomLook& lnf)> PaintFunction;

    PaintFunction paintBackground;
    PaintFunction paintMain;
    PaintFunction paintUpdates;

    StatesEnum state = main;

    std::array<PaintFunction, 2> paintStates { paintMain, paintUpdates };

    xynth::GuiData& guiData;
    xynth::TextButton siteButton, updatesButton, downloadButton;
    xynth::BackButton backButton;
    xynth::CheckmarkButton notifyUpdatesButton;

    juce::Image xynthLogo;

    xynth::UpdateChecker updateChecker;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AboutWindow)
};
