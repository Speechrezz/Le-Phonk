/*
  ==============================================================================

    ZeketeLayout.cpp
    Created: 5 Sep 2022 5:20:41pm
    Author:  thesp

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ZeketeLayout.h"

ZeketeLayout::ZeketeLayout(xynth::GuiData& g) : guiData(g)
{
    auto& treeState = g.audioProcessor.treeState;

    slider.init(treeState, ZEKETE_ID, ZEKETE_NAME);
    addAndMakeVisible(slider.slider);
}

ZeketeLayout::~ZeketeLayout()
{
}

void ZeketeLayout::paint (juce::Graphics& g)
{
    guiData.customLook.drawSectionBackground(g, getLocalBounds());
}

void ZeketeLayout::resized()
{
    auto rect = getLocalBounds().withSizeKeepingCentre(100, 100);
    slider.slider.setBounds(rect);
}
