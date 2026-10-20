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
    TimeKnob(GuiData&);
    ~TimeKnob() override = default;

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    GuiData& guiData;
    FullSlider timeKnob;
    DualLabel label;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TimeKnob)
};
} // namespace xynth