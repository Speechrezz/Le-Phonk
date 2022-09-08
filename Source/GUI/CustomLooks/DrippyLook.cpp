/*
  ==============================================================================

    HellLook.cpp
    Created: 5 Sep 2022 5:04:02pm
    Author:  thesp

  ==============================================================================
*/

#include "DrippyLook.h"

namespace juce
{

DrippyLook::DrippyLook()
{
    bgImage = juce::ImageCache::getFromMemory(BinaryData::drippyBG_png, BinaryData::drippyBG_pngSize);
}

Colour DrippyLook::getAccent1()
{
    return Colour::fromRGB(210, 82, 74);
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