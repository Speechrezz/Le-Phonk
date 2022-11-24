/*
  ==============================================================================

    AboutOverlay.cpp
    Created: 8 Sep 2022 5:08:12pm
    Author:  thesp

  ==============================================================================
*/

#include <JuceHeader.h>
#include "AboutOverlay.h"

AboutOverlay::AboutOverlay(xynth::GuiData& g) : guiData(g), aboutWindow(g), serverCheck(g)
{
    addAndMakeVisible(aboutWindow);
    serverCheck.updateCallback = [this](bool isUpdateAvailable)
    {
        DBG("Update callback");
    };
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
    serverCheck.checkForUpdates();
    auto rect = getLocalBounds().reduced(40, 190);
    aboutWindow.setBounds(rect);
}

void AboutOverlay::mouseDown(const juce::MouseEvent& e)
{
    if (!aboutWindow.isMouseOverOrDragging())
        setVisible(false);
}

void AboutOverlay::opened()
{
    aboutWindow.setState(AboutWindow::main);
}
