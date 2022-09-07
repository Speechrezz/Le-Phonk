/*
  ==============================================================================

    BypassButton.cpp
    Created: 7 Sep 2022 11:04:29am
    Author:  thesp

  ==============================================================================
*/

#include <JuceHeader.h>
#include "BypassButton.h"

BypassButton::BypassButton(xynth::GuiData& g) : guiData(g), 
    attach(g.audioProcessor.treeState, ENABLE_ID, *this)
{
}

BypassButton::~BypassButton()
{
}

void BypassButton::resized()
{
}
