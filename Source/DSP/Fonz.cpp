/*
  ==============================================================================

    Lemonz.cpp
    Created: 3 Sep 2022 9:48:14am
    Author:  thesp

  ==============================================================================
*/

#include "Fonz.h"
#include "../Common/Constants.h"
#include "../PluginProcessor.h"

constexpr float limit = 2.f;
constexpr float limitInv = 1.f / limit;
constexpr float limitSqr = limitInv * limitInv;

namespace xynth
{

static float distortSample(float x) noexcept
{
    x = juce::jlimit(-limit, limit, x);
    return x / (1 + x * x * limitSqr);
}

Fonz::Fonz(LePhonkAudioProcessor& processor) :
    paramAtomic(*processor.treeState.getRawParameterValue(FONZ_ID)),
    enableAtomic(*processor.treeState.getRawParameterValue(FONZ_ENABLE_ID))
{}

void Fonz::prepare(const juce::dsp::ProcessSpec& spec) noexcept
{
    gainIn.prepare(spec);
    gainIn.setRampDurationSeconds(0.005);

    gainOut.prepare(spec);
    gainOut.setRampDurationSeconds(0.005);
}

void Fonz::process(juce::dsp::ProcessContextReplacing<float>& context) noexcept
{
    // Check if enabled
    const bool enabled = enableAtomic.load(std::memory_order_relaxed) >= 0.5f;
    if (!enabled) return;

    const size_t numChannels = context.getInputBlock().getNumChannels();
    const size_t numSamples  = context.getInputBlock().getNumSamples();

    const float amount = paramAtomic.load(std::memory_order_relaxed) * 0.01f;
    const float dB = juce::jmap(amount, 0.f, 36.f);
    const float intensityIn = juce::Decibels::decibelsToGain(dB);
    gainIn.setGainLinear(intensityIn);

    const float avgGain = 0.15f;
    const float intensityOut = avgGain / distortSample(intensityIn * avgGain);
    gainOut.setGainLinear(intensityOut);

    gainIn.process(context);

    for (size_t ch = 0; ch < numChannels; ++ch)
    {
        float* channel = context.getOutputBlock().getChannelPointer(ch);
        for (size_t i = 0; i < numSamples; ++i)
        {
            channel[i] = distortSample(channel[i]);
        }
    }

    gainOut.process(context);
}

} // namespace xynth