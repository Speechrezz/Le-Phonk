/*
  ==============================================================================

    CustomLook.h
    Created: 5 Sep 2022 5:10:46pm
    Author:  thesp

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

namespace juce
{
class CustomLook : public LookAndFeel_V4
{
public:
    CustomLook() = default;

    virtual void drawSectionBackground(Graphics& g, Rectangle<int> area);
    virtual void drawDistGraphBackground(Graphics& g, Rectangle<float> area);
    virtual void drawDistGraphForeground(Graphics& g, Rectangle<float> area);
    void drawCornerResizer(Graphics& g, int w, int h, bool, bool) override;

    void drawRotarySlider(Graphics&, int x, int y, int width, int height, float sliderPosProportional,
        float rotaryStartAngle, float rotaryEndAngle, Slider&) override;

    void drawLinearSlider(Graphics& g, int x, int y, int width, int height, float sliderPos,
        float minSliderPos, float maxSliderPos, const Slider::SliderStyle style, Slider& slider) override;

    void drawToggleButton(Graphics&, ToggleButton&,
        bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override;

    virtual Colour getAccent1() = 0;
    virtual Colour getNeutral1() = 0;
    virtual Colour getBase1() = 0;

    virtual const juce::Font getCustomFontMedium();
    virtual const juce::Font getCustomFontSemiBold();

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CustomLook)
};
} // namespace juce