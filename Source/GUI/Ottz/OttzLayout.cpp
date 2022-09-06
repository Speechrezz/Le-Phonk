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

    slider.init(treeState, OTT_ID);
    addAndMakeVisible(slider.slider);
}

OttzLayout::~OttzLayout()
{
}

void OttzLayout::paint (juce::Graphics& g)
{
    auto rect = getLocalBounds();
    auto textRect = rect.removeFromTop(41);
    guiData.customLook.drawSectionBackground(g, rect);

    g.setColour(guiData.customLook.getAccent1());
    g.setFont(guiData.customLook.getCustomFontSemiBold());
    g.drawText("Le Ottz", textRect, juce::Justification::centredTop);
}

void OttzLayout::resized()
{
    auto rect = getLocalBounds();
    rect.removeFromTop(41);
    rect = rect.withSizeKeepingCentre(74, 74);
    slider.slider.setBounds(rect);
}