/*
  ==============================================================================

    HellLook.cpp
    Created: 5 Sep 2022 5:04:02pm
    Author:  thesp

  ==============================================================================
*/

#include "HellLook.h"

namespace juce
{
void HellLook::drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos,
    float rotaryStartAngle, float rotaryEndAngle, juce::Slider& slider)
{
    const auto bgColour = neutral1;
    const auto mainColour = accent1;

    // If mouse is hovering over
    const bool highlight = slider.isMouseOverOrDragging();

    float thickness = highlight ? 6.f : 5.f;

    // Radius of knob
    float radius = juce::jmin(width / 2, height / 2);
    // Centre point (centreX, centreY) of knob
    const float centreX = x + width * 0.5f;
    const float centreY = y + height * 0.5f;

    // Draw background circle
    Rectangle<float> rect(x, y, width, height);
    rect = rect.withSizeKeepingCentre(radius * 2.f, radius * 2.f);
    g.fillEllipse(rect);

    // current angle of the slider
    const float angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
    
    radius = juce::jmin(width / 2, height / 2) - thickness * 0.5f;

    // Draw path of the slider backgound (in darker background colour)
    juce::Path backgroundArc;
    backgroundArc.addCentredArc(centreX, centreY, radius, radius, 0.0f, rotaryStartAngle, rotaryEndAngle, true);
    g.setColour(bgColour);
    g.strokePath(backgroundArc, juce::PathStrokeType(thickness, juce::PathStrokeType::curved, juce::PathStrokeType::rounded));

    // Draw path of slider foreground (in white)
    juce::Path foregroundArc;
    foregroundArc.addCentredArc(centreX, centreY, radius, radius, 0.0f, rotaryStartAngle, angle, true);
    g.setColour(mainColour);
    g.strokePath(foregroundArc, juce::PathStrokeType(thickness, juce::PathStrokeType::curved, juce::PathStrokeType::rounded));
}
} // namespace juce