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

void CustomLook::drawCornerResizer(Graphics& g, int w, int h, bool, bool)
{}
} // namespace juce