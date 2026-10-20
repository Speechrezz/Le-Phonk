/*
  ==============================================================================

    Dist4.h
    Created: 10 Sep 2022 9:39:35am
    Author:  thesp

  ==============================================================================
*/

#pragma once

#include "DistortionProcessor.h"

namespace xynth
{

class Dist4 : public DistortionProcessor
{
public:
    Dist4() = default;
    ~Dist4() override = default;

    void reset() noexcept final;
    void prepare(const juce::dsp::ProcessSpec& spec) noexcept final;
    void process(juce::dsp::ProcessContextReplacing<float>& context, float amount) noexcept final;

    static float distortSample(float sample) noexcept
    {
        float y = 1.f / (std::abs(sample) + 1.f) * std::sin(sample * juce::MathConstants<float>::halfPi);
        return y + std::tanh(sample * 0.2f);
    }

    // For visualization
    static float distortVisual(float sample, float amount = 0.f)
    { 
        const float dB = juce::jmap(amount, 0.f, ZEKETE_MAX_DB);
        const float gain = juce::Decibels::decibelsToGain(dB);

        return distortSample(sample * gain);
    }

    static float xAxis(float param)
    {
        return juce::mapToLog10(param, 1.f, 0.3f);
    }

private:
    juce::dsp::Gain<float> gainIn, gainOut;

    std::array<juce::dsp::ProcessorDuplicator<
        juce::dsp::IIR::Filter<float>,
        juce::dsp::IIR::Coefficients<float>>, 2> filters;

    enum FiltersEnum { before, after };

};

} // namespace xynth