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
    const auto bgColour = getNeutral1();
    const auto mainColour = getAccent1();

    // If mouse is hovering over
    const bool highlight = slider.isMouseOverOrDragging();

    float thickness = highlight ? 5.f : 4.f;

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

    g.setFont(getCustomFontMedium());
    g.drawText(String(std::round(slider.getValue())), rect, Justification::centred);
}

void HellLook::drawLinearSlider(Graphics& g, int x, int y, int width, int height, float sliderPos, 
    float minSliderPos, float maxSliderPos, const Slider::SliderStyle style, Slider& slider)
{
    // If mouse is hovering over
    const bool highlight = slider.isMouseOverOrDragging();
    //const float trackWidth = highlight ? 7.f : 6.f;
    const float trackWidth = 6.f;

    Point<float> startPoint(slider.isHorizontal() ? (float)x : (float)x + (float)width * 0.5f,
        slider.isHorizontal() ? (float)y + (float)height * 0.5f : (float)(height + y));

    Point<float> endPoint(slider.isHorizontal() ? (float)(width + x) : startPoint.x,
        slider.isHorizontal() ? startPoint.y : (float)y);

    Path backgroundTrack;
    backgroundTrack.startNewSubPath(startPoint);
    backgroundTrack.lineTo(endPoint);
    g.setColour(getBase1());
    g.strokePath(backgroundTrack, { trackWidth, PathStrokeType::curved, PathStrokeType::rounded });

    Path valueTrack;
    Point<float> minPoint, maxPoint, thumbPoint;

    auto kx = slider.isHorizontal() ? sliderPos : ((float)x + (float)width * 0.5f);
    auto ky = slider.isHorizontal() ? ((float)y + (float)height * 0.5f) : sliderPos;

    minPoint = startPoint;
    maxPoint = { kx, ky };

    auto thumbWidth = highlight ? 15.f : 14.f;

    valueTrack.startNewSubPath(minPoint);
    valueTrack.lineTo(maxPoint.translated(-0.2f, 0.f));
    g.setColour(getAccent1());
    g.strokePath(valueTrack, { trackWidth, PathStrokeType::curved, PathStrokeType::rounded });

    g.fillRoundedRectangle(Rectangle<float>(static_cast<float> (thumbWidth * .4f), static_cast<float> (thumbWidth)).withCentre(maxPoint), 3.f);
}

Colour HellLook::getAccent1()
{
    return Colour::fromRGB(210, 82, 74);
}

Colour HellLook::getNeutral1()
{
    return Colour::fromRGB(64, 45, 44);
}

Colour HellLook::getBase1()
{
    return Colour::fromRGB(27, 16, 15);
}
} // namespace juce