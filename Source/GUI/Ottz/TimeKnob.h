/*
  ==============================================================================

    TimeKnob.h
    Created: 25 Dec 2022 9:25:11am
    Author:  thesp

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../Utils/GuiData.h"
#include "../Utils/FullSlider.h"
#include "../Utils/DualLabel.h"

namespace xynth
{
class TimeKnob : public juce::Component
{
public:
    TimeKnob(xynth::GuiData&);
    ~TimeKnob() = default;

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    xynth::GuiData& guiData;
    xynth::FullSlider timeKnob;
    xynth::DualLabel label;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TimeKnob)
};
} // namespace xynth