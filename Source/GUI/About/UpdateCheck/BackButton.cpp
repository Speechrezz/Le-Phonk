/*
  ==============================================================================

    BackButton.cpp
    Created: 11 Nov 2022 6:12:03pm
    Author:  thesp

  ==============================================================================
*/

#include <JuceHeader.h>
#include "BackButton.h"

namespace xynth 
{
BackButton::BackButton(xynth::GuiData& g) : guiData(g)
{
    backArrow = juce::Drawable::createFromImageData(BinaryData::backArrow_svg, BinaryData::backArrow_svgSize);
}

void BackButton::paint(juce::Graphics& g)
{
    const auto newColour = guiData.getLnf().getAccent2();
    backArrow->replaceColour(previousColour, newColour);
    previousColour = newColour;

    auto rect = getLocalBounds().toFloat();
    auto& lnf = guiData.getLnf();

    if (isMouseOver())
    {
        const float sideLength = std::min(rect.getWidth(), rect.getHeight());
        g.setColour(lnf.getNeutral1().withAlpha(0.3f));
        g.fillRoundedRectangle(rect.withSizeKeepingCentre(sideLength, sideLength), 4.f);
    }

    backArrow->drawWithin(g, rect, juce::RectanglePlacement::xLeft, 1.f);
}

void BackButton::mouseEnter(const juce::MouseEvent& e)
{
    setMouseCursor(juce::MouseCursor::PointingHandCursor);
    juce::TextButton::mouseEnter(e);
}

void BackButton::mouseExit(const juce::MouseEvent& e)
{
    setMouseCursor(juce::MouseCursor::NormalCursor);
    juce::TextButton::mouseExit(e);
}
} // namespace xynth