/*
  ==============================================================================

    JuiceLook.cpp
    Created: 5 Sep 2022 5:04:02pm
    Author:  thesp

  ==============================================================================
*/

#include "JuiceLook.h"

namespace juce
{
JuiceLook::JuiceLook()
{
    bgImage = juce::ImageCache::getFromMemory(BinaryData::juiceBG_png, BinaryData::juiceBG_pngSize);
}

Colour JuiceLook::getAccent1()
{
    return Colour::fromRGB(153, 146, 243);
}

Colour JuiceLook::getAccent2()
{
    return Colour::fromRGB(146, 197, 243);
}

Colour JuiceLook::getNeutral1()
{
    return Colour::fromRGB(75, 84, 88);
}

Colour JuiceLook::getBase1()
{
    return Colour::fromRGB(33, 34, 38);
}
} // namespace juce