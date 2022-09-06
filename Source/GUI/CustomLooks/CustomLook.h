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

    void drawSectionBackground(Graphics& g, Rectangle<int> area);
    void drawCornerResizer(Graphics& g, int w, int h, bool, bool);

    virtual Colour getAccent1() = 0;
    virtual Colour getNeutral1() = 0;
    virtual Colour getBase1() = 0;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CustomLook)
};
} // namespace juce