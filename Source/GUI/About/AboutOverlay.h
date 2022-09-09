/*
  ==============================================================================

    AboutOverlay.h
    Created: 8 Sep 2022 5:08:12pm
    Author:  thesp

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "AboutWindow.h"
#include "../Utils/GuiData.h"

class AboutOverlay  : public juce::Component
{
public:
    AboutOverlay(xynth::GuiData&);
    ~AboutOverlay() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    void mouseDown(const juce::MouseEvent& e) override;

private:
    xynth::GuiData& guiData;
    AboutWindow aboutWindow;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AboutOverlay)
};
