/*
  ==============================================================================

    CheckmarkButton.cpp
    Created: 18 Dec 2022 6:12:03pm
    Author:  thesp

  ==============================================================================
*/

#include <JuceHeader.h>
#include "CheckmarkButton.h"

namespace xynth
{
 CheckmarkButton::CheckmarkButton(xynth::GuiData& g) : guiData(g)
{
     setClickingTogglesState(true);
}

void CheckmarkButton::paint(juce::Graphics& g)
{
    auto rect = getLocalBounds().toFloat();
    auto boxRect = rect.removeFromLeft(16.f).withSizeKeepingCentre(16.f, 16.f);
    auto& lnf = guiData.getLnf();
    const float thickness = 1.f;

    // Box
    auto mainColor = lnf.getNeutral1().brighter(isMouseOver() ? 0.9f : 0.7f);
    mainColor = mainColor.darker(isMouseButtonDown() ? 0.2f : 0.f);
    g.setColour(mainColor);
    if (getToggleState())
    {
        g.fillRoundedRectangle(boxRect, 2.f);
        g.setColour(lnf.getBase1());
        boxRect.reduce(3.f, 5.f);

        const float bottomX = boxRect.getCentreX() - 2.f;
        const float bottomY = boxRect.getBottom();

        g.drawLine(boxRect.getX(), boxRect.getCentreY(), bottomX, bottomY, 1.5f);
        g.drawLine(bottomX, bottomY, boxRect.getRight(), boxRect.getY(), 1.5f);
    }
    else
        g.drawRoundedRectangle(boxRect.reduced(thickness / 2.f), 2.f, thickness);

    // Text
    g.setColour(lnf.getNeutral1().brighter(.3f));
    g.setFont(lnf.getCustomFontRegular2().withHeight(22.f));
    g.drawText(buttonText, rect, juce::Justification::centred);
}

void CheckmarkButton::mouseEnter(const juce::MouseEvent& e)
{
    setMouseCursor(juce::MouseCursor::PointingHandCursor);
    juce::TextButton::mouseEnter(e);
}

void CheckmarkButton::mouseExit(const juce::MouseEvent& e)
{
    setMouseCursor(juce::MouseCursor::NormalCursor);
    juce::TextButton::mouseExit(e);
}

void CheckmarkButton::setText(const juce::String newText)
{
    buttonText = newText;
    repaint();
}
} // namespace xynth