/*
  ==============================================================================

    FonzLayout.cpp
    Created: 5 Sep 2022 5:44:16pm
    Author:  thesp

  ==============================================================================
*/

#include <JuceHeader.h>
#include "FonzLayout.h"

FonzLayout::FonzLayout(xynth::GuiData& g) : guiData(g)
{
    auto& treeState = g.audioProcessor.treeState;

    slider.init(treeState, FONZ_ID, FONZ_NAME);
    addAndMakeVisible(slider.slider);
}

FonzLayout::~FonzLayout()
{
}

void FonzLayout::paint (juce::Graphics& g)
{
    guiData.customLook.drawSectionBackground(g, getLocalBounds());
}

void FonzLayout::resized()
{
    auto rect = getLocalBounds().withSizeKeepingCentre(100, 100);
    slider.slider.setBounds(rect);
}
