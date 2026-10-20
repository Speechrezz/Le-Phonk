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

#if !JUCE_USE_SIMD
  #error "SIMD is NOT available"
#endif

namespace xynth
{

constexpr auto registerSize = juce::dsp::SIMDRegister<float>::size();

class SIMDFilter
{
public:
    using SimdRegister = juce::dsp::SIMDRegister<float>;
    using Coefficients = std::array<float, 6>;

public:
    SIMDFilter() = default;
    ~SIMDFilter() = default;

    void reset() noexcept
    {
        state[0] = 0.f;
        state[1] = 0.f;
    }

    SimdRegister processSample(SimdRegister input) noexcept
    {
        const float b0 = coeffs[0];
        const float b1 = coeffs[1];
        const float b2 = coeffs[2];
        const float a1 = coeffs[4];
        const float a2 = coeffs[5];

        auto lv1 = state[0];
        auto lv2 = state[1];

        const auto output = (input * b0) + lv1;

        lv1 = (input * b1) - (output* a1) + lv2;
        lv2 = (input * b2) - (output* a2);

        juce::dsp::util::snapToZero (lv1); state[0] = lv1;
        juce::dsp::util::snapToZero (lv2); state[1] = lv2;

        return output;
    }

    template<typename ContextType>
    void process(ContextType context) noexcept
    {
        const size_t numSamples = context.getInputBlock().getNumSamples();
        const auto* inputChannel = context.getInputBlock().getChannelPointer(0);
        auto* outputChannel = context.getOutputBlock().getChannelPointer(0);

        for (size_t i = 0; i < numSamples; ++i)
            outputChannel[i] = processSample(inputChannel[i]);
    }

    Coefficients coeffs;
    alignas(sizeof(SimdRegister)) SimdRegister state[2];

};

} // namespace xynth