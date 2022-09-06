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

    slider.init(treeState, ZEKETE_ID);
    addAndMakeVisible(slider.slider);
}

ZeketeLayout::~ZeketeLayout()
{
}

void ZeketeLayout::paint (juce::Graphics& g)
{
    g.setColour(guiData.customLook.getAccent1());
    g.drawHorizontalLine(46, 29, getWidth() - 29);

    guiData.customLook.drawSectionBackground(g, getLocalBounds());
}

void ZeketeLayout::resized()
{
    auto rect = getLocalBounds().withSizeKeepingCentre(74, 74);
    slider.slider.setBounds(rect);
}
