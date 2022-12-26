/*
  ==============================================================================

    Ranges.cpp
    Created: 15 Dec 2022 10:12:12am
    Author:  thesp

  ==============================================================================
*/

#include "Ranges.h"
#include "Constants.h"

namespace xynth
{
    juce::NormalisableRange<float> createRange(const float minVal, const float maxVal, const float midVal)
    {
        juce::NormalisableRange<float> range(minVal, maxVal);
        range.setSkewForCentre(midVal);
        return range;
    }

    juce::NormalisableRange<float> createFrequencyRange(const float minFreq, const float maxFreq)
    {
        return juce::NormalisableRange<float>(minFreq, maxFreq,
            // ---convertFrom0To1Func---
            [](float rangeStart, float rangeEnd, float valueToRemap) -> float
            {
                return juce::mapToLog10<float>(valueToRemap, rangeStart, rangeEnd);
            },
            // ---convertTo0To1Func---
                [](float rangeStart, float rangeEnd, float valueToRemap) -> float
            {
                return juce::mapFromLog10<float>(valueToRemap, rangeStart, rangeEnd);
            }, {});
    }

    juce::NormalisableRange<float> createRatioRange()
    {
        juce::NormalisableRange<float> range(1.f, 20.f);
        range.setSkewForCentre(4.f);
        return range;
    }

    /*juce::NormalisableRange<float> createDecibelRange()
    {
        juce::NormalisableRange<float> range(DECIBEL_MINIMUM, 12.f);
        range.setSkewForCentre(-18.f);
        return range;
    }*/
} // namespace xynth