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

    Colour getAccent1() override;
    Colour getNeutral1() override;
    Colour getBase1() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HellLook)
};
} // namespace juce