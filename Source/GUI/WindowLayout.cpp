/*
  ==============================================================================

    WindowLayout.cpp
    Created: 5 Sep 2022 3:26:44pm
    Author:  thesp

  ==============================================================================
*/

#include <JuceHeader.h>
#include "WindowLayout.h"

//==============================================================================
WindowLayout::WindowLayout(xynth::GuiData& g) : guiData(g)
{
    auto& treeState = g.audioProcessor.treeState;

    Zekete.init(treeState, ZEKETE_ID, ZEKETE_NAME);
    OTT.init(treeState, OTT_ID, OTT_NAME);
    Lemonz.init(treeState, LEMONZ_ID, LEMONZ_NAME);

    addAndMakeVisible(Zekete.slider);
    addAndMakeVisible(OTT.slider);
    addAndMakeVisible(Lemonz.slider);

    backgroundImage = juce::ImageCache::getFromMemory(BinaryData::hellBG_png, BinaryData::hellBG_pngSize);
}

WindowLayout::~WindowLayout()
{
}

void WindowLayout::paint (juce::Graphics& g)
{
    auto rect = getLocalBounds();
    g.drawImageWithin(backgroundImage, rect.getX(), rect.getY(), rect.getWidth(), rect.getHeight(), juce::RectanglePlacement::fillDestination);
}

void WindowLayout::resized()
{
    auto rect = getLocalBounds().withTrimmedTop(200).reduced(20, 0);

    Zekete.slider.setBounds(rect.removeFromTop(120));
    rect.removeFromTop(100);
    OTT.slider.setBounds(rect.removeFromTop(120));
    rect.removeFromTop(100);
    Lemonz.slider.setBounds(rect.removeFromTop(120));
}
