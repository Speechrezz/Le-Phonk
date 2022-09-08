/*
  ==============================================================================

    JuiceLook.h
    Created: 5 Sep 2022 5:04:02pm
    Author:  thesp

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "CustomLook.h"

namespace juce
{
class JuiceLook : public CustomLook
{
public:
    JuiceLook();

    String getLnfName() override { return "JuiceLook"; }
    Image& getBackgroundImage() override { return bgImage; };

    Colour getAccent1() override;
    Colour getAccent2() override;
    Colour getNeutral1() override;
    Colour getBase1() override;

private:
    Image bgImage;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JuiceLook)
};
} // namespace juce