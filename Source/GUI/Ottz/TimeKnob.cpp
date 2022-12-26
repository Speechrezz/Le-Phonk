/*
  ==============================================================================

    TimeKnob.cpp
    Created: 25 Dec 2022 9:25:11am
    Author:  thesp

  ==============================================================================
*/

#include <JuceHeader.h>
#include "TimeKnob.h"

namespace xynth
{
TimeKnob::TimeKnob(xynth::GuiData& g) : guiData(g), label(timeKnob.slider)
{
    auto& treeState = g.audioProcessor.treeState;

    timeKnob.init(treeState, OTT_TIME_ID);
    addAndMakeVisible(timeKnob.slider);

    label.setText("Test", juce::dontSendNotification);
    label.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(label);
}

void TimeKnob::paint(juce::Graphics& g)
{
    timeKnob.slider.setColour(juce::Slider::rotarySliderFillColourId,    guiData.getLnf().getNeutral1());
    timeKnob.slider.setColour(juce::Slider::rotarySliderOutlineColourId, guiData.getLnf().getAccent1());

    label.setFont(guiData.getLnf().getCustomFontRegular2());
    label.setColour(juce::Label::textColourId, guiData.getLnf().getAccent1());
}

void TimeKnob::resized()
{
    auto rect = getLocalBounds();
    rect = rect.withSizeKeepingCentre(32, 32);
    timeKnob.slider.setBounds(rect);

    juce::Rectangle<int> labelRect(rect.getX(), rect.getBottom(), rect.getWidth(), 20);
    label.setBounds(labelRect.withSizeKeepingCentre(getWidth(), labelRect.getHeight()));
}

} // namespace xynth