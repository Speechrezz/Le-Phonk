/*
  ==============================================================================

    SIMDFilter.cpp
    Created: 9 Sep 2022 5:30:35pm
    Author:  thesp

  ==============================================================================
*/

#include "SIMDFilter.h"

namespace xynth
{

using Coefficients = juce::dsp::IIR::ArrayCoefficients<float>;

SIMDFilter::SIMDFilter()
{
    jassert(JUCE_USE_SIMD); // Make sure CPU has SIMD before compiling

    using namespace juce::dsp;

    // Initialize filter
    iirCoefficients = IIR::Coefficients<float>::makeAllPass(44100.0, 200.f);
    iir = std::make_unique<IIR::Filter<SIMDRegister<float>>>(iirCoefficients);
}

void SIMDFilter::prepare(const juce::dsp::ProcessSpec& spec)
{
    sampleRate = spec.sampleRate;

    auto monoSpec = spec;
    monoSpec.numChannels = 1;
    iir->prepare(monoSpec);
}

void SIMDFilter::process(juce::dsp::AudioBlock<juce::dsp::SIMDRegister<float>>& interleaved)
{
    using namespace juce::dsp;

    iir->process(ProcessContextReplacing<SIMDRegister<float>>(interleaved));
}

void SIMDFilter::updateParameters(float cutoff, float Q)
{
    if (sampleRate != 0.0)
        *iirCoefficients = Coefficients::makeAllPass(sampleRate, cutoff, Q);
}

} // namespace xynth