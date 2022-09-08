/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "GUI/WindowLayout.h"
#include "GUI/Utils/GuiData.h"

class LePhonkAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    LePhonkAudioProcessorEditor (LePhonkAudioProcessor&);
    ~LePhonkAudioProcessorEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    juce::SharedResourcePointer<xynth::DefaultLookAndFeel> defaultLnf;

private:
    LePhonkAudioProcessor& audioProcessor;
    xynth::GuiData guiData;
    WindowLayout windowLayout;

    // Stores global plugin settings
    juce::ApplicationProperties properties;
    double scale{ 1.0 };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LePhonkAudioProcessorEditor)
};
