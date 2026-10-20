/*
  ==============================================================================

    Dist6.h
    Created: 10 Sep 2022 9:39:35am
    Author:  thesp

  ==============================================================================
*/

#pragma once

#include "DistortionProcessor.h"

namespace xynth
{

class Dist6 : public DistortionProcessor
{
public:
    Dist6() = default;
    ~Dist6() override = default;

    void reset() noexcept final;
    void prepare(const juce::dsp::ProcessSpec& spec) noexcept final;
    void process(juce::dsp::ProcessContextReplacing<float>& context, float amount) noexcept final;

    static float distortSample(float sample) noexcept
    {
        sample = 0.25f * (sample + 1.f);
        float y = 4.f * std::abs(sample - std::floor(sample + 0.5f)) - 1.f;
        return y;
    }

    // For visualization
    static float distortVisual(float sample, float amount)
    { 
        const float dB = juce::jmap(amount, 0.f, ZEKETE_MAX_DB);
        const float gain = juce::Decibels::decibelsToGain(dB);

        return distortSample(sample * gain);
    }
    static float xAxis(float amount)
    {
        return juce::mapToLog10(amount, 1.f, 0.3f);
    }

private:
    juce::dsp::Gain<float> gainIn, gainOut;

    std::array<juce::dsp::ProcessorDuplicator<
        juce::dsp::IIR::Filter<float>,
        juce::dsp::IIR::Coefficients<float>>, 3> filters;

    std::array<juce::dsp::ProcessorDuplicator<
        juce::dsp::IIR::Filter<float>,
        juce::dsp::IIR::Coefficients<float>>, 3> allPassFilters;

    enum FiltersEnum { before1, before2, after };

};

} // namespace xynth