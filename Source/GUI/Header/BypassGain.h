/*
  ==============================================================================

    BypassGain.h
    Created: 7 Sep 2022 10:45:40am
    Author:  thesp

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "GUI/Utils/GuiData.h"
#include "GUI/Utils/TooltipSlider.h"
#include "BypassButton.h"

class BypassGain : public juce::Component
{
public:
    BypassGain(xynth::GuiData&);
    ~BypassGain() override = default;

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    xynth::GuiData& guiData;
    xynth::BypassButton bypassButton;
    xynth::TooltipSlider gainSlider;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(BypassGain)
};
