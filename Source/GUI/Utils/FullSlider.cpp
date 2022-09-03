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
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 150, 25);
    slider.setTextBoxIsEditable(true);

    label.setJustificationType(juce::Justification::centred);
    label.attachToComponent(&slider, false);
}

void FullSlider::init(juce::AudioProcessorValueTreeState& treeState, juce::String paramID, juce::String labelText)
{
    attach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(treeState, paramID, slider);
    label.setText(labelText, juce::dontSendNotification);
}
} // namespace xynth