/*
  ==============================================================================

    HellLook.cpp
    Created: 5 Sep 2022 5:04:02pm
    Author:  thesp

  ==============================================================================
*/

#include "DrippyLook.h"
#include "../../Common/Constants.h"

namespace juce
{

DrippyLook::DrippyLook()
{
    bgImage =       juce::ImageCache::getFromMemory(BinaryData::drippyBG_png, BinaryData::drippyBG_pngSize);
    danGraphImage = juce::ImageCache::getFromMemory(BinaryData::danBG_png,    BinaryData::danBG_pngSize);

    // Randomize knob images
    struct ImageAndSize
    {
        const char* imageData;
        int imageSize;
    };

    ImageAndSize knobImageArray[] = {
        {BinaryData::skyKnob_png,    BinaryData::skyKnob_pngSize},
        {BinaryData::peteKnob_png,   BinaryData::peteKnob_pngSize},
        {BinaryData::speechKnob_png, BinaryData::speechKnob_pngSize},
        {BinaryData::sharkKnob_png,  BinaryData::sharkKnob_pngSize},
        {BinaryData::danKnob_png,    BinaryData::danKnob_pngSize},
        {BinaryData::exylKnob_png,   BinaryData::exylKnob_pngSize},
        {BinaryData::eliKnob_png,    BinaryData::eliKnob_pngSize},
        {BinaryData::au5Knob_png,    BinaryData::au5Knob_pngSize},
    };

    const int arrayLength = 8;
    const int randomIndex1 = random.nextInt(arrayLength);
    int randomIndex2 = random.nextInt(arrayLength - 1);
    if (randomIndex2 >= randomIndex1) // prevent same images for both knobs
        randomIndex2++;

    const auto randomImage1 = knobImageArray[randomIndex1];
    const auto randomImage2 = knobImageArray[randomIndex2];
    
    ottKnobImage  = juce::ImageCache::getFromMemory(randomImage1.imageData, randomImage1.imageSize);
    fonzKnobImage = juce::ImageCache::getFromMemory(randomImage2.imageData, randomImage2.imageSize);
}

void DrippyLook::drawSectionBackground(Graphics& g, Rectangle<int> area)
{
    g.setColour(Colour::fromRGB(43, 41, 37));
    g.fillRoundedRectangle(area.toFloat(), 8.f);
}
void DrippyLook::drawDistGraphBackground(Graphics& g, Rectangle<float> area, float amp)
{
    g.setColour(getBase1());
    g.fillRoundedRectangle(area, 8.f);

    if (amp > prevAmp)
    {
        prevAmp = amp;
        hold = 20;
    }
    else if (hold >= 0)
        --hold;
    else
        prevAmp *= 0.96f;

    g.setOpacity(prevAmp * 0.8f);
    g.drawImageWithin(danGraphImage, area.getX(), area.getY(), area.getWidth(), area.getHeight(), juce::RectanglePlacement::fillDestination);

    g.setOpacity(1.f);
    g.setColour(getNeutral1().withAlpha(0.5f));
    g.drawLine(area.getCentreX(), area.getY(), area.getCentreX(), area.getBottom(), 2.f);
    g.drawLine(area.getX(), area.getCentreY(), area.getRight(), area.getCentreY(), 2.f);
}

void DrippyLook::drawRotarySlider(Graphics& g, int x, int y, int width, int height, 
    float sliderPos, float rotaryStartAngle, float rotaryEndAngle, Slider& slider)
{
    auto desc = slider.getDescription();
    Image& knobImage = desc == OTT_NAME ? ottKnobImage : fonzKnobImage;

    // If mouse is hovering over
    const bool highlight = slider.isMouseOverOrDragging();

    // Radius of knob
    float radius = juce::jmin(width / 2, height / 2);
    const bool isLarge = radius > 25.f;

    if (!isLarge)
    {
        CustomLook::drawRotarySlider(g, x, y, width, height, sliderPos, rotaryStartAngle, rotaryEndAngle, slider);
        return;
    }

    // Centre point (centreX, centreY) of knob
    const float centreX = x + width * 0.5f;
    const float centreY = y + height * 0.5f;

    float thickness = (highlight ? 5.f : 4.4f) * (isLarge ? 1.f : 0.6f);

    // current angle of the slider
    const float imageAngle = sliderPos * (rotaryEndAngle - rotaryStartAngle);
    const float angle = rotaryStartAngle + imageAngle;

    // Draw background circle
    Rectangle<float> rect(x, y, width, height);
    rect = rect.withSizeKeepingCentre(radius * 2.f, radius * 2.f);
    g.setColour(getBase1());
    g.fillEllipse(rect.reduced(0.1f));

    // Draw image
    g.setOpacity(0.8f);
    AffineTransform trans;
    trans = trans.rotation(imageAngle, centreX, centreY);
    trans = trans.scaled(0.9f, 0.9f, centreX, centreY);
    g.drawImageTransformed(knobImage, trans);
    g.setOpacity(1.f);

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

    // Draw text
    /*Path textPath;
    GlyphArrangement glyphs;
    auto font = getCustomFontBold().withHeight(24.f);
    auto text = String(std::round(slider.getValue()));
    glyphs.addFittedText(font, text, x, y, width, height, juce::Justification::centred, 2);
    glyphs.createPath(textPath);

    g.setColour(getBase1());
    juce::PathStrokeType strokeType(6.f);
    g.strokePath(textPath, strokeType);
    g.setColour(mainColour);
    g.fillPath(textPath);*/
}

Colour DrippyLook::getAccent1()
{
    return Colour::fromRGB(255, 14, 0);
}

Colour DrippyLook::getAccent2()
{
    return getAccent1();
}

Colour DrippyLook::getNeutral1()
{
    return Colour::fromRGB(64, 45, 44);
}

Colour DrippyLook::getBase1()
{
    return Colour::fromRGB(27, 16, 15);
}
} // namespace juce