/*
  ==============================================================================

    TooltipSlider.cpp
    Created: 25 Dec 2022 6:55:51pm
    Author:  thesp

  ==============================================================================
*/

#include <JuceHeader.h>
#include "TooltipSlider.h"

namespace xynth
{
TooltipSlider::TooltipSlider(xynth::GuiData& g) : guiData(g)
{
    setSliderStyle(juce::Slider::RotaryVerticalDrag);
    setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
}

void TooltipSlider::mouseEnter(const juce::MouseEvent& e)
{
    guiData.showTooltip(this, name);
    guiData.updateTooltipValue(juce::String(getValue(), 2));
    juce::Slider::mouseEnter(e);
}

void TooltipSlider::mouseExit(const juce::MouseEvent& e)
{
    guiData.hideTooltip();
    juce::Slider::mouseExit(e);
}

void TooltipSlider::assignParameter(const juce::String& paramID)
{
    attach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(guiData.audioProcessor.treeState, paramID, *this);
}

void TooltipSlider::setName(const juce::String& newName)
{
    name = newName;
}

void TooltipSlider::valueChanged()
{
    if (isMouseOverOrDragging())
        guiData.updateTooltipValue(juce::String(getValue(), 2));
}

void TooltipSlider::resized()
{
    juce::Slider::resized();
}
} // namespace xynth