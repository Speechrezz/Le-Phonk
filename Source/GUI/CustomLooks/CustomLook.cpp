/*
  ==============================================================================

    CustomLook.cpp
    Created: 5 Sep 2022 5:10:46pm
    Author:  thesp

  ==============================================================================
*/

#include "CustomLook.h"

namespace juce
{
void CustomLook::drawSectionBackground(Graphics& g, Rectangle<int> area)
{
    g.setColour(Colours::black.withAlpha(0.3f));
    g.fillRoundedRectangle(area.toFloat(), 8.f);
}

void CustomLook::drawDistGraphBackground(Graphics& g, Rectangle<float> area)
{
    g.setColour(getBase1());
    g.fillRoundedRectangle(area, 8.f);

    g.setColour(getNeutral1());
    g.drawLine(area.getCentreX(), area.getY(), area.getCentreX(), area.getBottom(), 2.f);
    g.drawLine(area.getX(), area.getCentreY(), area.getRight(), area.getCentreY(), 2.f);
}

void CustomLook::drawDistGraphForeground(Graphics& g, Rectangle<float> area)
{
    g.setColour(getAccent1());
    g.drawRoundedRectangle(area.reduced(0.75f), 8.f, 2.f);
}

void CustomLook::drawCornerResizer(Graphics& g, int w, int h, bool, bool)
{}

const juce::Font CustomLook::getCustomFontMedium()
{
    static auto typeface = juce::Typeface::createSystemTypefaceFor(BinaryData::MuseoModernoMedium_ttf, BinaryData::MuseoModernoMedium_ttfSize);
    return juce::Font(typeface).withHeight(36.f);
}

const juce::Font CustomLook::getCustomFontSemiBold()
{
    static auto typeface = juce::Typeface::createSystemTypefaceFor(BinaryData::MuseoModernoSemiBold_ttf, BinaryData::MuseoModernoSemiBold_ttfSize);
    return juce::Font(typeface).withHeight(44.f);
}
} // namespace juce