/*
  ==============================================================================

    DualLabel.cpp
    Created: 25 Dec 2022 10:13:24am
    Author:  thesp

  ==============================================================================
*/

#include <JuceHeader.h>
#include "DualLabel.h"

namespace xynth
{
DualLabel::DualLabel(juce::Slider& s) : parentSlider(s)
{}

void DualLabel::paint(juce::Graphics& g)
{
    if (parentSlider.isMouseOverOrDragging() || isMouseOverOrDragging())
    {
        auto value = parentSlider.getValue();
        const auto newText = value > 99.9 ? juce::String(std::round(value)) : juce::String(value, 1);
        setText(newText + "%", juce::dontSendNotification);
    }
    else
        setText("Time", juce::dontSendNotification);

    juce::Label::paint(g);
}

void DualLabel::mouseEnter(const juce::MouseEvent& e)
{
    repaint();
}

void DualLabel::mouseExit(const juce::MouseEvent& e)
{
    repaint();
}
} // namespace xynth