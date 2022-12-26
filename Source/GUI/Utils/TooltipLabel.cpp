/*
  ==============================================================================

    TooltipLabel.cpp
    Created: 25 Dec 2022 2:03:01pm
    Author:  thesp

  ==============================================================================
*/

#include <JuceHeader.h>
#include "TooltipLabel.h"

namespace xynth
{
TooltipLabel::TooltipLabel(xynth::GuiData& g) : guiData(g)
{
    //setAlwaysOnTop(true);
}

void TooltipLabel::paint(juce::Graphics& g)
{
    auto& lnf = guiData.getLnf();

    g.setColour(lnf.getBase1());
    g.fillRoundedRectangle(getLocalBounds().toFloat(), 4.f);

    const auto text = prefixText + ": " + valueText; // + juce::String(parentSlider.getValue());
    g.setColour(lnf.getNeutral1().brighter(.8f));
    g.drawText(text, getLocalBounds(), juce::Justification::centred, false);
}

void TooltipLabel::resized()
{
}

void TooltipLabel::showTooltip(juce::Point<int> screenPosition, const juce::String& newPrefixText)
{
    setVisible(true);
    prefixText = newPrefixText;

    juce::Rectangle<int> rect(screenPosition, screenPosition);
    rect.expand(50, 0);
    rect.setHeight(20);
    setBounds(rect);
    repaint();
}

void TooltipLabel::updateTooltipValue(const juce::String& newValue)
{
    valueText = newValue;
    repaint();
}

void TooltipLabel::hideTooltip()
{
    setVisible(false);
    repaint();
}
} // namespace xynth