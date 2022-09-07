/*
  ==============================================================================

    HellLook.cpp
    Created: 5 Sep 2022 5:04:02pm
    Author:  thesp

  ==============================================================================
*/

#include "HellLook.h"

namespace juce
{
Colour HellLook::getAccent1()
{
    return Colour::fromRGB(210, 82, 74);
}

Colour HellLook::getNeutral1()
{
    return Colour::fromRGB(64, 45, 44);
}

Colour HellLook::getBase1()
{
    return Colour::fromRGB(27, 16, 15);
}
} // namespace juce