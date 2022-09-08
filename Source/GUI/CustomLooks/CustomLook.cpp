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
CustomLook::CustomLook()
{
    // Ensures the background of popup menus is transparent
    // allows corners to be rounded
    setColour(PopupMenu::backgroundColourId, Colours::black.withAlpha(0.0f));
}

void CustomLook::drawSectionBackground(Graphics& g, Rectangle<int> area)
{
    g.setColour(Colours::black.withAlpha(0.3f));
    g.fillRoundedRectangle(area.toFloat(), 8.f);
}

void CustomLook::drawDistGraphBackground(Graphics& g, Rectangle<float> area, float)
{
    g.setColour(getBase1());
    g.fillRoundedRectangle(area, 8.f);

    g.setColour(getNeutral1().withAlpha(0.5f));
    g.drawLine(area.getCentreX(), area.getY(), area.getCentreX(), area.getBottom(), 2.f);
    g.drawLine(area.getX(), area.getCentreY(), area.getRight(), area.getCentreY(), 2.f);
}

void CustomLook::drawDistGraphForeground(Graphics& g, Rectangle<float> area)
{
    g.setColour(getAccent2());
    g.drawRoundedRectangle(area.reduced(0.75f), 8.f, 2.f);
}

void CustomLook::drawCornerResizer(Graphics& g, int w, int h, bool, bool)
{}

void CustomLook::drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos,
    float rotaryStartAngle, float rotaryEndAngle, juce::Slider& slider)
{
    // If mouse is hovering over
    const bool highlight = slider.isMouseOverOrDragging();

    // Radius of knob
    float radius = juce::jmin(width / 2, height / 2);
    const bool isLarge = radius > 25.f;

    // Centre point (centreX, centreY) of knob
    const float centreX = x + width * 0.5f;
    const float centreY = y + height * 0.5f;

    float thickness = (highlight ? 5.f : 4.4f) * (isLarge ? 1.f : 0.6f);

    // Draw background circle
    Rectangle<float> rect(x, y, width, height);
    rect = rect.withSizeKeepingCentre(radius * 2.f, radius * 2.f);
    g.setColour(getBase1());
    g.fillEllipse(rect.reduced(0.1f));

    // current angle of the slider
    const float angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);

    radius = juce::jmin(width / 2, height / 2) - thickness * 0.5f;

    const auto bgColour = getNeutral1();
    const auto mainColour = isLarge ? getAccent1() : getAccent2();

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

    if (isLarge)
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
    g.setColour(getAccent2());
    g.strokePath(valueTrack, { trackWidth, PathStrokeType::curved, PathStrokeType::rounded });

    g.fillRoundedRectangle(Rectangle<float>(static_cast<float> (thumbWidth * .4f), static_cast<float> (thumbWidth)).withCentre(maxPoint), 3.f);
}

void CustomLook::drawToggleButton(Graphics& g, ToggleButton& button,
    bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown)
{
    auto rect = button.getLocalBounds().toFloat();

    // Draw background
    auto bgColour = button.getToggleState() ? getAccent2() : getNeutral1();
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

void CustomLook::drawComboBox(Graphics& g, int width, int height, bool isButtonDown, int buttonX, 
    int buttonY, int buttonW, int buttonH, ComboBox& box)
{
    const float cornerSize = 4.f;
    Rectangle<int> boxBounds(0, 0, width, height);

    const bool isMouseDown = box.isMouseOver(true);

    // Draw background
    auto bgColour = getAccent2();
    bgColour = bgColour.brighter(isMouseDown ? 0.1f : 0.f);
    bgColour = bgColour.darker(isButtonDown ? 0.2f : 0.f);
    g.setColour(bgColour);
    g.fillRoundedRectangle(boxBounds.toFloat(), cornerSize);

    Rectangle<int> arrowZone(width - 24, 0, 18, height);
    Path path;
    path.startNewSubPath((float)arrowZone.getX() + 3.0f, (float)arrowZone.getCentreY() - 2.0f);
    path.lineTo((float)arrowZone.getCentreX(), (float)arrowZone.getCentreY() + 4.0f);
    path.lineTo((float)arrowZone.getRight() - 3.0f, (float)arrowZone.getCentreY() - 2.0f);

    g.setColour(getBase1());
    g.strokePath(path, PathStrokeType(2.0f, PathStrokeType::mitered, PathStrokeType::rounded));
}

Font CustomLook::getComboBoxFont(ComboBox& box)
{
    return getCustomFontBold();
}

void CustomLook::positionComboBoxText(ComboBox& box, Label& label)
{
    label.setBounds(4, 4, box.getWidth() - 30, box.getHeight() - 8);
    label.setColour(Label::ColourIds::textColourId, getBase1());
    label.setFont(getComboBoxFont(box));
    label.setJustificationType(juce::Justification::centred);
}

void CustomLook::drawPopupMenuItem(Graphics& g, const Rectangle<int>& area, bool isSeparator, bool isActive, 
    bool isHighlighted, bool isTicked, bool hasSubMenu, const String& text, const String& shortcutKeyText, 
    const Drawable* icon, const Colour* textColourToUse)
{
    auto textColour = getAccent2();

    auto r = area.reduced(1);

    if (isHighlighted && isActive)
    {
        g.setColour(getNeutral1());
        g.fillRect(r);

        g.setColour(textColour.brighter(1.f));
    }
    else
    {
        g.setColour(textColour.withMultipliedAlpha(isActive ? 1.0f : 0.5f));
    }

    r.reduce(jmin(5, area.getWidth() / 20), 0);

    auto font = getCustomFontSemiBold();

    auto maxFontHeight = (float)r.getHeight() / 1.2f;

    if (font.getHeight() > maxFontHeight)
        font.setHeight(maxFontHeight);

    g.setFont(font);

    auto iconArea = r.removeFromLeft(roundToInt(maxFontHeight)).toFloat();
    if (isTicked)
    {
        auto tick = getTickShape(1.0f);
        g.fillPath(tick, tick.getTransformToScaleToFit(iconArea.reduced(iconArea.getWidth() / 5, 0).toFloat(), true));
    }

    r.removeFromRight(3);
    g.drawFittedText(text, r, Justification::centredLeft, 1);
}

void CustomLook::drawPopupMenuBackground(Graphics& g, int width, int height)
{
    const Rectangle<float> rect(width, height);

    g.setColour(getBase1());
    g.fillRoundedRectangle(rect, 4.f);
    g.setColour(getNeutral1());
    g.drawRoundedRectangle(rect, 4.f, 2.f);
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
const juce::Font CustomLook::getCustomFontBold()
{
    static auto typeface = juce::Typeface::createSystemTypefaceFor(BinaryData::MuseoModernoBold_ttf, BinaryData::MuseoModernoBold_ttfSize);
    return juce::Font(typeface).withHeight(28.f);
}
} // namespace juce