/*
  ==============================================================================

    Ranges.h
    Created: 15 Dec 2022 10:12:12am
    Author:  thesp

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

namespace xynth
{
    juce::NormalisableRange<float> createRange(const float minVal, const float maxVal, const float midVal);
    juce::NormalisableRange<float> createFrequencyRange(const float minFreq, const float maxFreq);
    juce::NormalisableRange<float> createRatioRange();
    //juce::NormalisableRange<float> createDecibelRange();
} // namespace xynth