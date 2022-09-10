/*
  ==============================================================================

    SIMDFilter.h
    Created: 9 Sep 2022 5:30:35pm
    Author:  thesp

    This code is lightly modified JUCE code from:
    https://docs.juce.com/master/tutorial_simd_register_optimisation.html

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>


namespace xynth
{
constexpr auto registerSize = juce::dsp::SIMDRegister<float>::size();

class SIMDFilter
{
public:
    SIMDFilter();
    ~SIMDFilter() = default;

    void prepare(const juce::dsp::ProcessSpec& spec);
    void process(juce::dsp::AudioBlock<juce::dsp::SIMDRegister<float>>& interleaved);

    void updateParameters(float cutoff, float Q = 0.70710678f);

private:
    std::unique_ptr<juce::dsp::IIR::Filter<juce::dsp::SIMDRegister<float>>> iir;
    juce::dsp::IIR::Coefficients<float>::Ptr iirCoefficients;

    double sampleRate = 0.0;

};
} // namespace xynth