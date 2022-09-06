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
class HellLook  : public juce::CustomLook
{
public:
    Colour accent1 = Colour::fromRGB(210, 82, 74);
    Colour neutral1 = Colour::fromRGB(64, 45, 44);
    Colour base1 = Colour::fromRGB(27, 16, 15);

    HellLook() = default;

    void drawRotarySlider(Graphics&, int x, int y, int width, int height, float sliderPosProportional,
        float rotaryStartAngle, float rotaryEndAngle, Slider&) override;


private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HellLook)
};
} // namespace juce