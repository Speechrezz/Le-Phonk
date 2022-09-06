/*
  ==============================================================================

    FullSlider.cpp
    Created: 31 Aug 2022 10:32:20am
    Author:  thesp

  ==============================================================================
*/

#include "FullSlider.h"

namespace xynth
{
FullSlider::FullSlider()
{
    slider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    slider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    slider.setTextBoxIsEditable(true);
}

void FullSlider::init(juce::AudioProcessorValueTreeState& treeState, juce::String paramID)
{
    attach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(treeState, paramID, slider);
}
} // namespace xynth