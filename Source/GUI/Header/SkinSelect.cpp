/*
  ==============================================================================

    SkinSelect.cpp
    Created: 7 Sep 2022 3:08:25pm
    Author:  thesp

  ==============================================================================
*/

#include <JuceHeader.h>
#include "SkinSelect.h"

SkinSelect::SkinSelect(xynth::GuiData& g) : guiData(g)
{
    dropDown.addItemList(skinNames, 1);
    dropDown.setJustificationType(juce::Justification::centred);
    dropDown.setText("Le Skins", notif);
    dropDown.onChange = [this]() { updateSkin(); };

    addAndMakeVisible(dropDown);
}

SkinSelect::~SkinSelect()
{
}

void SkinSelect::paint (juce::Graphics& g)
{
}

void SkinSelect::resized()
{
    dropDown.setBounds(getLocalBounds());
}

void SkinSelect::mouseEnter(const juce::MouseEvent& e)
{
    dropDown.repaint();
}

void SkinSelect::mouseExit(const juce::MouseEvent& e)
{
    dropDown.repaint();
}

void SkinSelect::updateSkin()
{
    const auto idx = dropDown.getSelectedId();
    guiData.updateLnf(idx - 1);
}
