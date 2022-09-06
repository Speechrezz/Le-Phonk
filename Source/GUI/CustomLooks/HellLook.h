/*
  ==============================================================================

    HellLook.h
    Created: 5 Sep 2022 5:04:02pm
    Author:  thesp

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "CustomLook.h"

namespace juce
{
class HellLook  : public CustomLook
{
public:
    HellLook() = default;

    void drawRotarySlider(Graphics&, int x, int y, int width, int height, float sliderPosProportional,
        float rotaryStartAngle, float rotaryEndAngle, Slider&) override;

    void drawLinearSlider(Graphics& g, int x, int y, int width, int height, float sliderPos,
        float minSliderPos, float maxSliderPos, const Slider::SliderStyle style, Slider& slider) override;

    Colour getAccent1() override;
    Colour getNeutral1() override;
    Colour getBase1() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HellLook)
};
} // namespace juce