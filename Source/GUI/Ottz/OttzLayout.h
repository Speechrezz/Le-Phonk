/*
  ==============================================================================

    OttzLayout.h
    Created: 5 Sep 2022 5:44:06pm
    Author:  thesp

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../Utils/GuiData.h"
#include "../Utils/FullSlider.h"
#include "../Header/BypassButton.h"
#include "TimeKnob.h"

class OttzLayout  : public juce::Component
{
public:
    OttzLayout(xynth::GuiData&);
    ~OttzLayout() = default;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    xynth::GuiData& guiData;
    xynth::FullSlider slider;
    xynth::TimeKnob timeKnob;
    xynth::BypassButton toggleButton;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OttzLayout)
};
