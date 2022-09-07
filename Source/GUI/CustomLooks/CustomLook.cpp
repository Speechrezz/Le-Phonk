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

void CustomLook::drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos,
    float rotaryStartAngle, float rotaryEndAngle, juce::Slider& slider)
{
    const auto bgColour = getNeutral1();
    const auto mainColour = getAccent1();

    // If mouse is hovering over
    const bool highlight = slider.isMouseOverOrDragging();

    // Radius of knob
    float radius = juce::jmin(width / 2, height / 2);
    // Centre point (centreX, centreY) of knob
    const float centreX = x + width * 0.5f;
    const float centreY = y + height * 0.5f;

    float thickness = (highlight ? 5.f : 4.f) * (radius > 25.f ? 1.f : 0.6f);

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

    if (radius > 25.f)
    {
        g.setFont(getCustomFontMedium());
        g.drawText(String(std::round(slider.getValue())), rect, Justification::centred);
    }
}

void CustomLook::drawLinearSlider(Graphics& g, int x, int y, int width, int height, float sliderPos,
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

void CustomLook::drawToggleButton(Graphics& g, ToggleButton& button,
    bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown)
{
    auto rect = button.getLocalBounds().toFloat();

    // Draw background
    auto bgColour = button.getToggleState() ? getAccent1() : getNeutral1();
    bgColour = bgColour.brighter(shouldDrawButtonAsHighlighted ? 0.1f : 0.f);
    bgColour = bgColour.darker(shouldDrawButtonAsDown ? 0.2f : 0.f);
    g.setColour(bgColour);
    g.fillRoundedRectangle(rect, 6.f);

    // Draw power symbol
    g.setColour(getBase1());
    const float centreX = rect.getCentreX();
    const float centreY = rect.getCentreY();

    Path p;
    const float margin = 0.5f;
    p.addCentredArc(centreX, centreY, 5.f, 5.f, 1.5708f, -margin, 3.14 + margin, true);

    p.startNewSubPath(centreX, centreY - 2.f);
    p.lineTo(centreX, centreY - 5.f);

    g.strokePath(p, juce::PathStrokeType(2.5f, juce::PathStrokeType::mitered, juce::PathStrokeType::rounded));
}


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