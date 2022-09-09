/*
  ==============================================================================

    DistTemplate.h
    Created: 9 Sep 2022 9:39:23am
    Author:  thesp

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../../Common/Constants.h"

namespace xynth
{
class DistTemplate
{
public:
    DistTemplate() = default;
    ~DistTemplate() = default;

    virtual void prepare(const juce::dsp::ProcessSpec& spec);
    virtual void process(juce::dsp::ProcessContextReplacing<float>& context);
    virtual inline float distort(float sample) { return sample; }

    virtual void setAtomics(juce::AudioProcessorValueTreeState& treeState);

private:

};
} // namespace xynth