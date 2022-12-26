/*
  ==============================================================================

    BypassButton.cpp
    Created: 7 Sep 2022 11:04:29am
    Author:  thesp

  ==============================================================================
*/

#include <JuceHeader.h>
#include "BypassButton.h"

namespace xynth
{
BypassButton::BypassButton(xynth::GuiData& g, juce::String parameterId) : guiData(g),
    attach(g.audioProcessor.treeState, parameterId, *this)
{}
} // namespace xynth