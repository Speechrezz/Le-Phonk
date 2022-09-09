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

    /// <summary>
    /// Prepares audio processing.
    /// </summary>
    /// <param name="spec">->struct which contains samplerate, number of channels, etc.</param>
    virtual void prepare(const juce::dsp::ProcessSpec& spec) = 0;

    /// <summary>
    /// Does the audio processing.
    /// </summary>
    /// <param name="context">-> Incoming audio data</param>
    virtual void process(juce::dsp::ProcessContextReplacing<float>& context) = 0;

    /// <summary>
    /// Optional function, which is responsible for telling the GUI what the distortion looks like.
    /// Should contain a copy of your distortion equation.
    /// </summary>
    /// <param name="sample">-> input sample</param>
    /// <returns>Distorted sample</returns>
    virtual inline float distort(float sample) { return sample; }

    /// <summary>
    /// This method will save any pointers to audio parameters.
    /// </summary>
    /// <param name="treeState">-> a reference to the AudioParamterValueTreeState object</param>
    virtual void setAtomics(juce::AudioProcessorValueTreeState& treeState) = 0;

private:

};
} // namespace xynth