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

    Colour getAccent1() override;
    Colour getAccent2() override;
    Colour getNeutral1() override;
    Colour getBase1() override;

private:
    Image bgImage;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DrippyLook)
};
} // namespace juce