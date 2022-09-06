/*
  ==============================================================================

    OttzLayout.cpp
    Created: 5 Sep 2022 5:44:06pm
    Author:  thesp

  ==============================================================================
*/

#include <JuceHeader.h>
#include "OttzLayout.h"

OttzLayout::OttzLayout(xynth::GuiData& g) : guiData(g)
{
    auto& treeState = g.audioProcessor.treeState;

    slider.init(treeState, OTT_ID, OTT_NAME);
    addAndMakeVisible(slider.slider);
}

OttzLayout::~OttzLayout()
{
}

void OttzLayout::paint (juce::Graphics& g)
{
    guiData.customLook.drawSectionBackground(g, getLocalBounds());
}

void OttzLayout::resized()
{
    auto rect = getLocalBounds().withSizeKeepingCentre(100, 100);
    slider.slider.setBounds(rect);
}
