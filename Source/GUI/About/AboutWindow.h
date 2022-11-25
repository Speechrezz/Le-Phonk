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
#include "WebsiteButton.h"
#include "UpdatesButton.h"
#include "UpdateCheck/BackButton.h"
#include "UpdateCheck/UpdateChecker.h"

class AboutWindow  : public juce::Component
{
public:
    AboutWindow(xynth::GuiData&);

    void paint(juce::Graphics&) override;
    void resized() override;

    void setState(const int newState);
    enum States{ main, updates };

private:
    void initPaintFunctions();

    typedef std::function<void(juce::Graphics& g, juce::Rectangle<float>& rect, juce::CustomLook& lnf)> PaintFunction;

    PaintFunction paintBackground;
    PaintFunction paintMain;
    PaintFunction paintUpdates;

    int state = main;

    std::array<PaintFunction, 2> paintStates { paintMain, paintUpdates };

    xynth::GuiData& guiData;
    WebsiteButton siteButton;
    UpdatesButton updatesButton;
    BackButton backButton;

    juce::Image xynthLogo;

    xynth::UpdateChecker updateChecker;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AboutWindow)
};
