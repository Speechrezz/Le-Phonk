/*
  ==============================================================================

    DistSelect.cpp
    Created: 8 Sep 2022 4:01:58pm
    Author:  thesp

  ==============================================================================
*/

#include <JuceHeader.h>
#include "DistSelect.h"

DistSelect::DistSelect(xynth::GuiData& g) : guiData(g)
{
    dropDown.addItemList(guiData.audioProcessor.distTypes, 1);
    dropDown.setJustificationType(juce::Justification::centred);
    dropDown.setScrollWheelEnabled(true);

    dropDownAttach = std::make_unique<cbAttach>(g.audioProcessor.treeState, DIST_SELECT_ID, dropDown);

    addAndMakeVisible(dropDown);
}

DistSelect::~DistSelect()
{
}

void DistSelect::paint (juce::Graphics& g)
{
}

void DistSelect::resized()
{
    dropDown.setBounds(getLocalBounds());
}

void DistSelect::mouseEnter(const juce::MouseEvent& e)
{
    dropDown.repaint();
}

void DistSelect::mouseExit(const juce::MouseEvent& e)
{
    dropDown.repaint();
}
