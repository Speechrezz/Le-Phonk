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
SIMDFilter::SIMDFilter()
{
    // make sure CPU has SIMD before compiling
    jassert(JUCE_USE_SIMD);
}

void SIMDFilter::prepare(const juce::dsp::ProcessSpec& spec)
{
    using namespace juce::dsp;

    sampleRate = spec.sampleRate;

    iirCoefficients = IIR::Coefficients<float>::makeAllPass(sampleRate, 200.f);
    iir.reset(new IIR::Filter<SIMDRegister<float>>(iirCoefficients));

    auto monoSpec = spec;
    monoSpec.numChannels = 1;
    iir->prepare(monoSpec);
}
void SIMDFilter::process(juce::dsp::AudioBlock<juce::dsp::SIMDRegister<float>>& interleaved)
{
    using namespace juce;
    using namespace dsp;

    iir->process(ProcessContextReplacing<SIMDRegister<float>>(interleaved));
}

void SIMDFilter::updateParameters(float cutoff, float Q)
{
    if (sampleRate != 0.0)
        *iirCoefficients = *juce::dsp::IIR::Coefficients<float>::makeAllPass(sampleRate, cutoff, Q);
}

} // namespace xynth