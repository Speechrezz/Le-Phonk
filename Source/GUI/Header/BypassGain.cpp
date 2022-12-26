/*
  ==============================================================================

    BypassGain.cpp
    Created: 7 Sep 2022 10:45:40am
    Author:  thesp

  ==============================================================================
*/

#include <JuceHeader.h>
#include "BypassGain.h"

BypassGain::BypassGain(xynth::GuiData& g) : guiData(g), bypassButton(g, ENABLE_ID), gainSlider(g)
{
    gainSlider.assignParameter(GAIN_ID);
    gainSlider.setName("Gain");
    gainSlider.setPostfix("dB");

    addAndMakeVisible(gainSlider);
    addAndMakeVisible(bypassButton);
}

void BypassGain::paint(juce::Graphics& g)
{
    gainSlider.setColour(juce::Slider::rotarySliderFillColourId,    guiData.getLnf().getNeutral1());
    gainSlider.setColour(juce::Slider::rotarySliderOutlineColourId, guiData.getLnf().getAccent2());

    bypassButton.setColour(juce::ToggleButton::ColourIds::tickColourId, guiData.getLnf().getAccent2());
    bypassButton.setColour(juce::ToggleButton::ColourIds::tickDisabledColourId, guiData.getLnf().getNeutral1());
}

void BypassGain::resized()
{
    auto rect = getLocalBounds().reduced(0, 9);

    bypassButton.setBounds(rect.removeFromRight(20));
    rect.removeFromRight(9);
    gainSlider.setBounds(rect);
    rect.translate(0, rect.getHeight() / 2);
}
