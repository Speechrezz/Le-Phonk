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
    juce::Slider::mouseEnter(e);
    guiData.showTooltip(this);
    valueChanged();
}

void TooltipSlider::mouseExit(const juce::MouseEvent& e)
{
    juce::Slider::mouseExit(e);
    guiData.hideTooltip();
}

void TooltipSlider::assignParameter(const juce::String& paramID)
{
    attach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(guiData.audioProcessor.treeState, paramID, *this);
}

void TooltipSlider::valueChanged()
{
    if (!isMouseOverOrDragging()) return;

    auto tooltipText = name + ": " + juce::String(getValue(), 1) + postfix;
    guiData.updateTooltipText(tooltipText);
}

void TooltipSlider::resized()
{
    juce::Slider::resized();
}
} // namespace xynth