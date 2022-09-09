/*
  ==============================================================================

    AboutOverlay.cpp
    Created: 8 Sep 2022 5:08:12pm
    Author:  thesp

  ==============================================================================
*/

#include <JuceHeader.h>
#include "AboutOverlay.h"

AboutOverlay::AboutOverlay(xynth::GuiData& g) : guiData(g), aboutWindow(g)
{
    addAndMakeVisible(aboutWindow);
}

AboutOverlay::~AboutOverlay()
{
}

void AboutOverlay::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::black.withAlpha(0.7f));
}

void AboutOverlay::resized()
{
    auto rect = getLocalBounds().reduced(40, 200);
    aboutWindow.setBounds(rect);
}

void AboutOverlay::mouseDown(const juce::MouseEvent& e)
{
    
    if (!aboutWindow.isMouseOverOrDragging())
        setVisible(false);
}
