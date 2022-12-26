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
    setAlwaysOnTop(true);
}

void TooltipLabel::paint(juce::Graphics& g)
{
    auto& lnf = guiData.getLnf();

    auto bgRect = getLocalBounds().toFloat();
    g.setColour(lnf.getBase1());
    g.fillRoundedRectangle(bgRect, 4.f);

    g.setColour(lnf.getNeutral1().brighter(1.f));
    g.drawText(tooltipText, getLocalBounds(), juce::Justification::centred, false);

    g.setColour(lnf.getAccent2());
    g.drawRoundedRectangle(bgRect.reduced(0.25f), 4.f, 1.f);
}

void TooltipLabel::showTooltip(juce::Point<int> screenPosition)
{
    setVisible(true);

    juce::Rectangle<int> rect(screenPosition, screenPosition);
    rect.expand(50, 0);
    rect.setHeight(20);
    setBounds(rect);
    repaint();
}

void TooltipLabel::updateTooltipText(const juce::String& newText)
{
    tooltipText = newText;
    repaint();
}

void TooltipLabel::hideTooltip()
{
    setVisible(false);
    repaint();
}
} // namespace xynth