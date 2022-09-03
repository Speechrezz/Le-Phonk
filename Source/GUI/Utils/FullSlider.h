/*
  ==============================================================================

    FullSlider.h
    Created: 31 Aug 2022 10:32:20am
    Author:  thesp

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

namespace xynth
{
class FullSlider
{
public:
    FullSlider();
    ~FullSlider() = default;

    void init(juce::AudioProcessorValueTreeState& treeState, juce::String paramID, juce::String labelText = "");

    juce::Slider slider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> attach;
    juce::Label label;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FullSlider)
};
} //namespace xynth