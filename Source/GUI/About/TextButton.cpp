/*
  ==============================================================================

    TextButton.cpp
    Created: 18 Dec 2022 6:12:03pm
    Author:  thesp

  ==============================================================================
*/

#include <JuceHeader.h>
#include "TextButton.h"

namespace xynth
{
TextButton::TextButton(xynth::GuiData& g) : guiData(g)
{}

void TextButton::paint(juce::Graphics& g)
{
    auto rect = getLocalBounds().toFloat();
    auto& lnf = guiData.getLnf();
    const float thickness = 1.5f;

    auto mainCol = lnf.getAccent2().brighter(isMouseOver() ? 0.15f : 0.f);
    mainCol = mainCol.darker(isMouseButtonDown() ? 0.2f : 0.f);
    g.setColour(mainCol);
    g.drawRoundedRectangle(rect.reduced(thickness / 2.f), 6.f, thickness);

    g.setFont(lnf.getCustomFontMedium().withHeight(24.f));
    g.drawText(buttonText, rect, juce::Justification::centred);
}

void TextButton::mouseEnter(const juce::MouseEvent& e)
{
    setMouseCursor(juce::MouseCursor::PointingHandCursor);
    juce::TextButton::mouseEnter(e);
}

void TextButton::mouseExit(const juce::MouseEvent& e)
{
    setMouseCursor(juce::MouseCursor::NormalCursor);
    juce::TextButton::mouseExit(e);
}

void TextButton::setFillIn(const bool shouldFillIn)
{
    fillInButton = shouldFillIn;
    repaint();
}

void TextButton::setText(const juce::String newText)
{
    buttonText = newText;
    repaint();
}
} // namespace xynth