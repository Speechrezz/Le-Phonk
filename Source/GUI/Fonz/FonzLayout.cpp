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

    slider.init(treeState, FONZ_ID);
    addAndMakeVisible(slider.slider);
}

FonzLayout::~FonzLayout()
{
}

void FonzLayout::paint (juce::Graphics& g)
{
    auto rect = getLocalBounds();
    auto textRect = rect.removeFromTop(41);
    guiData.customLook.drawSectionBackground(g, rect);

    g.setColour(guiData.customLook.getAccent1());
    g.setFont(guiData.customLook.getCustomFontSemiBold());
    g.drawText("Le Fonz", textRect, juce::Justification::centredTop);
}

void FonzLayout::resized()
{
    auto rect = getLocalBounds();
    rect.removeFromTop(41);
    rect = rect.withSizeKeepingCentre(74, 74);
    slider.slider.setBounds(rect);
}