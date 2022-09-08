/*
  ==============================================================================

    WindowLayout.cpp
    Created: 5 Sep 2022 3:26:44pm
    Author:  thesp

  ==============================================================================
*/

#include <JuceHeader.h>
#include "WindowLayout.h"

WindowLayout::WindowLayout(xynth::GuiData& g) : guiData(g), zeketeLayout(g), ottzLayout(g), 
    fonzLayout(g), bypassGain(g), skinSelect(g)
{
    auto& treeState = g.audioProcessor.treeState;

    addAndMakeVisible(zeketeLayout);
    addAndMakeVisible(ottzLayout);
    addAndMakeVisible(fonzLayout);
    addAndMakeVisible(bypassGain);
    addAndMakeVisible(skinSelect);
}

WindowLayout::~WindowLayout()
{
}

void WindowLayout::paint (juce::Graphics& g)
{
    auto rect = getLocalBounds();
    g.drawImageWithin(guiData.getLnf().getBackgroundImage(), rect.getX(), rect.getY(), rect.getWidth(), rect.getHeight(), juce::RectanglePlacement::fillDestination);
}

void WindowLayout::resized()
{
    const int spacing = 18;

    auto rect = getLocalBounds();
    auto headerRect = rect.removeFromTop(130).withTrimmedBottom(25).reduced(29, 0);
    rect.reduce(58, 0);

    zeketeLayout.setBounds(rect.removeFromTop(354));
    rect.removeFromTop(spacing);
    ottzLayout.setBounds(rect.removeFromTop(129));
    rect.removeFromTop(spacing);
    fonzLayout.setBounds(rect.removeFromTop(129));

    bypassGain.setBounds(headerRect.removeFromBottom(44).removeFromRight(54));

    skinSelect.setBounds(headerRect.removeFromRight(114)
        .withTrimmedTop(8).withSizeKeepingCentre(114, 32));
}
