/*
  ==============================================================================

    BypassGain.h
    Created: 7 Sep 2022 10:45:40am
    Author:  thesp

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../Utils/GuiData.h"
#include "../Utils/FullSlider.h"
#include "../Utils/TooltipSlider.h"
#include "BypassButton.h"

class BypassGain : public juce::Component
{
public:
    BypassGain(xynth::GuiData&);
    ~BypassGain() = default;

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    xynth::GuiData& guiData;
    xynth::BypassButton bypassButton;
    //xynth::FullSlider gain;
    xynth::TooltipSlider gainSlider;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(BypassGain)
};
