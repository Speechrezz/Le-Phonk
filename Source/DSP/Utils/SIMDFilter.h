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
    using SimdRegister = juce::dsp::SIMDRegister<float>;
    using Coefficients = std::array<float, 6>;

public:
    SIMDFilter() = default;
    ~SIMDFilter() = default;

    void reset() noexcept;
    SimdRegister processSample(SimdRegister sample) noexcept;

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
    std::array<SimdRegister, 2> state;

};

} // namespace xynth