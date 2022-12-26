/*
  ==============================================================================

    ParameterText.cpp
    Created: 30 Sep 2022 11:54:19pm
    Author:  thesp

  ==============================================================================
*/

#include "ParameterText.h"
#include "Constants.h"

namespace xynth
{
    juce::String frequencyAsText(float value, int)
    {
        if (value >= 1000.f) 
        {
            value = value / 1000.f;
            return juce::String(value, 2) + " kHz";
        }

        return juce::String(value, 2) + " Hz";
    }

    juce::String msAsText(float value, int maxLength)
    {
        if (value >= 1000.f)
        {
            value /= 1000.f;
            return juce::String(value, 2) + " s";
        }

        return juce::String(value, 2) + " ms";
    }

    juce::String valueAsText(float value, int)
    {
        return juce::String(value, 2);
    }

    std::array<juce::String, 12> noteNameArray = { "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B" };

    juce::String midiValueAsNoteName(float value, int)
    {
        const int index = int(value) % 12;
        const int octave = (int(value) / 12);

        return noteNameArray[index] + juce::String(octave);
    }
} // namespace xynth