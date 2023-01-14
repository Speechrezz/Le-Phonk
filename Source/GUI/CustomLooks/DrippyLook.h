/*
  ==============================================================================

    DrippyLook.h
    Created: 5 Sep 2022 5:04:02pm
    Author:  thesp

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "CustomLook.h"

namespace juce
{
class DrippyLook : public CustomLook
{
public:
    DrippyLook();

    String getLnfName() override { return "DrippyLook"; }
    Image& getBackgroundImage() override { return bgImage; };

    // Custom draws
    void drawSectionBackground(Graphics& g, Rectangle<int> area) override;
    void drawDistGraphBackground(Graphics& g, Rectangle<float> area, float amplitude) override;

    void drawRotarySlider(Graphics&, int x, int y, int width, int height, float sliderPosProportional,
        float rotaryStartAngle, float rotaryEndAngle, Slider&) override;

    Colour getAccent1() override;
    Colour getAccent2() override;
    Colour getNeutral1() override;
    Colour getBase1() override;

private:
    Image bgImage, danGraphImage, ottKnobImage, fonzKnobImage;

    juce::Random random;

    float prevAmp{ 0.f };
    int hold{ 0 };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DrippyLook)
};
} // namespace juce