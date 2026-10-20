/*
  ==============================================================================

    Zekete.h
    Created: 3 Sep 2022 11:27:40am
    Author:  thesp

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Zekete/ZeketeRegistry.h"

class LePhonkAudioProcessor;

namespace xynth
{

class Zekete
{
public:
    Zekete(LePhonkAudioProcessor&);
    ~Zekete() = default;

    void reset() noexcept;
    void prepare(const juce::dsp::ProcessSpec& spec) noexcept;
    void process(juce::dsp::ProcessContextReplacing<float>& context) noexcept;

private:
    juce::dsp::DryWetMixer<float> mixer;

    std::atomic<float>& distTypeParam;
    std::atomic<float>& mixParam;
    std::atomic<float>& amountParam;

    size_t distType = 0;

    juce::dsp::ProcessSpec spec;
    std::unique_ptr<DistortionProcessor> distortion;

};

} // namespace xynth