/*
  ==============================================================================

    BypassGain.cpp
    Created: 7 Sep 2022 10:45:40am
    Author:  thesp

  ==============================================================================
*/

#include <JuceHeader.h>
#include "BypassGain.h"

BypassGain::BypassGain(xynth::GuiData& g) : guiData(g), bypassButton(g)
{
    gain.init(g.audioProcessor.treeState, GAIN_ID);

    addAndMakeVisible(gain.slider);
    addAndMakeVisible(bypassButton);
}

BypassGain::~BypassGain()
{
}

void BypassGain::paint (juce::Graphics& g)
{
}

void BypassGain::resized()
{
    auto rect = getLocalBounds().reduced(0, 9);

    bypassButton.setBounds(rect.removeFromRight(20));
    rect.removeFromRight(9);
    DBG(rect.getHeight() << ", " << rect.getWidth());
    gain.slider.setBounds(rect);
}
