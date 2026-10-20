/*
  ==============================================================================

    Dist1.h
    Created: 9 Sep 2022 9:39:35am
    Author:  thesp

  ==============================================================================
*/

#pragma once

#include "DistortionProcessor.h"

namespace xynth
{

class Dist1 : public DistortionProcessor
{
public:
    Dist1() = default;
    ~Dist1() override = default;

    void reset() noexcept final;
    void prepare(const juce::dsp::ProcessSpec& spec) noexcept final;
    void process(juce::dsp::ProcessContextReplacing<float>& context, float amount) noexcept final;

    static float distortSample(float sample) noexcept
    {
        return std::tanh(sample);
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
        juce::dsp::IIR::Coefficients<float>>, 2> filters;

    enum FiltersEnum { before, after };
};

} // namespace xynth