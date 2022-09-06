/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "GUI/WindowLayout.h"
#include "GUI/CustomLooks/HellLook.h"

struct DefaultLookAndFeel
{
    DefaultLookAndFeel() { juce::LookAndFeel::setDefaultLookAndFeel(&lnf); }
    ~DefaultLookAndFeel() { juce::LookAndFeel::setDefaultLookAndFeel(nullptr); }

    // Change to desired LookAndFeel
    juce::HellLook lnf;
};

class LePhonkAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    LePhonkAudioProcessorEditor (LePhonkAudioProcessor&);
    ~LePhonkAudioProcessorEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::SharedResourcePointer<DefaultLookAndFeel> defaultLnf;
    LePhonkAudioProcessor& audioProcessor;
    xynth::GuiData guiData;
    WindowLayout windowLayout;

    double scale{ 1.0 };

    // Stores global plugin settings
    juce::ApplicationProperties properties;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LePhonkAudioProcessorEditor)
};
