/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "GUI/Utils/FullSlider.h"

//==============================================================================
/**
*/
class LePhonkAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    LePhonkAudioProcessorEditor (LePhonkAudioProcessor&);
    ~LePhonkAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    LePhonkAudioProcessor& audioProcessor;

    xynth::FullSlider OTT, Lemonz, Zekete;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LePhonkAudioProcessorEditor)
};
