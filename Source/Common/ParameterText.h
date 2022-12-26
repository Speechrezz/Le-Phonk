/*
  ==============================================================================

    ParameterText.h
    Created: 30 Sep 2022 11:54:19pm
    Author:  thesp

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

namespace xynth
{
    juce::String frequencyAsText(float value, int maxLength = 2);
    juce::String msAsText(float value, int maxLength = 2);
    juce::String valueAsText(float value, int maxLength = 2);
    juce::String midiValueAsNoteName(float value, int maxLength = 2);
} // namespace xynth