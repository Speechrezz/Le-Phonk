/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

LePhonkAudioProcessorEditor::LePhonkAudioProcessorEditor (LePhonkAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    setSize (400, 800);

    auto& treeState = audioProcessor.treeState;

    Zekete.init(treeState, ZEKETE_ID, ZEKETE_NAME);
    OTT.init   (treeState, OTT_ID,    OTT_NAME);
    Lemonz.init(treeState, LEMONZ_ID, LEMONZ_NAME);

    addAndMakeVisible(Zekete.slider);
    addAndMakeVisible(OTT.slider);
    addAndMakeVisible(Lemonz.slider);
}

LePhonkAudioProcessorEditor::~LePhonkAudioProcessorEditor()
{
}

void LePhonkAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (24.0f);
    g.drawFittedText ("Le Phonk", getLocalBounds().removeFromTop(60), juce::Justification::centred, 1);
}

void LePhonkAudioProcessorEditor::resized()
{
    auto rect = getLocalBounds().withTrimmedTop(200).reduced(20, 0);

    Zekete.slider.setBounds(rect.removeFromTop(120));
    rect.removeFromTop(100);
    OTT.slider.setBounds(rect.removeFromTop(120));
    rect.removeFromTop(100);
    Lemonz.slider.setBounds(rect.removeFromTop(120));
}
