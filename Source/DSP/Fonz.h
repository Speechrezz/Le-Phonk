/*
  ==============================================================================

    Lemonz.h
    Created: 3 Sep 2022 9:48:14am
    Author:  thesp

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class LePhonkAudioProcessor;

namespace xynth
{

class Fonz
{
public:
    Fonz(LePhonkAudioProcessor&);
    ~Fonz() = default;

    void prepare(const juce::dsp::ProcessSpec& spec) noexcept;
    void process(juce::dsp::ProcessContextReplacing<float>& context) noexcept;

private:
    juce::dsp::Gain<float> gainIn, gainOut;

    std::atomic<float>& paramAtomic;
    std::atomic<float>& enableAtomic;

};

} // namespace xynth