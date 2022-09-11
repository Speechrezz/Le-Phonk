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
    addItemList(guiData.audioProcessor.distTypes, 1);
    setJustificationType(juce::Justification::centred);
    setScrollWheelEnabled(true);

    dropDownAttach = std::make_unique<cbAttach>(g.audioProcessor.treeState, DIST_SELECT_ID, *this);
}

void DistSelect::mouseEnter(const juce::MouseEvent& e)
{
    repaint();
}

void DistSelect::mouseExit(const juce::MouseEvent& e)
{
    repaint();
}

void DistSelect::mouseWheelMove(const juce::MouseEvent& e, const juce::MouseWheelDetails& mw)
{
    const int curItem = getSelectedItemIndex();
    const int maxIdx = getNumItems() - 1;
    const float threshold = 0.35f;
    mwMovement += mw.deltaY;

    if (mwMovement > threshold)
    {
        setSelectedItemIndex(std::max(curItem - 1, 0));
        mwMovement = 0.f;
    }
    else if (mwMovement < -threshold)
    {
        setSelectedItemIndex(std::min(curItem + 1, maxIdx));
        mwMovement = 0.f;
    }
    
    //juce::ComboBox::mouseWheelMove(e, mw);
}
