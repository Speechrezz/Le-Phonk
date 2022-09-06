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

    virtual Colour getAccent1() = 0;
    virtual Colour getNeutral1() = 0;
    virtual Colour getBase1() = 0;

    virtual const juce::Font getCustomFontMedium();
    virtual const juce::Font getCustomFontSemiBold();

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CustomLook)
};
} // namespace juce