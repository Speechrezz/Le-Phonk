/*
  ==============================================================================

    DistTemplate.h
    Created: 9 Sep 2022 9:39:23am
    Author:  thesp

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Common/Constants.h"

namespace xynth
{

class DistortionProcessor
{
public:
    DistortionProcessor() = default;
    virtual ~DistortionProcessor() = default;

    virtual void reset() noexcept {}
    virtual void prepare(const juce::dsp::ProcessSpec& /** spec */) noexcept = 0;

    // `amount` is normalized to be between 0 and 1
    virtual void process(juce::dsp::ProcessContextReplacing<float>&, float /** amount */) noexcept = 0;

};

} // namespace xynth