/*
  ==============================================================================

    Dist2.cpp
    Created: 9 Sep 2022 9:39:35am
    Author:  thesp

  ==============================================================================
*/

#include "Dist2.h"

namespace xynth
{

void Dist2::reset() noexcept
{
    for (auto& filter : filters)
        filter.reset();

    for (auto& filter : allPassFilters)
        filter.reset();
}

void Dist2::prepare(const juce::dsp::ProcessSpec& spec) noexcept
{
    gainIn.prepare(spec);
    gainIn.setRampDurationSeconds(0.005);

    gainOut.prepare(spec);
    gainOut.setRampDurationSeconds(0.005);

    for (auto& filter : filters)
        filter.prepare(spec);

    *filters[before].state = *juce::dsp::IIR::Coefficients<float>::makePeakFilter(spec.sampleRate, 1000.f, 0.3f, 2.f);
    *filters[after].state  = *juce::dsp::IIR::Coefficients<float>::makePeakFilter(spec.sampleRate, 1000.f, 0.3f, 1.f / 2.f);

    float cutoff = 200.f;
    const float cutoffStep = 25.f;
    for (auto& filter : allPassFilters)
    {
        filter.prepare(spec);
        *filter.state = *juce::dsp::IIR::Coefficients<float>::makeAllPass(spec.sampleRate, cutoff);
        cutoff += cutoffStep;
    }
}

void Dist2::process(juce::dsp::ProcessContextReplacing<float>& context, float amount) noexcept
{
    const size_t numChannels = context.getInputBlock().getNumChannels();
    const size_t numSamples  = context.getInputBlock().getNumSamples();

    const float dB = juce::jmap(amount, 0.f, ZEKETE_MAX_DB);
    const float intensityIn = juce::Decibels::decibelsToGain(dB);
    gainIn.setGainLinear(intensityIn);

    constexpr float avgGain = 0.15f;
    const float intensityOut = avgGain / distortSample(intensityIn * avgGain);
    gainOut.setGainLinear(intensityOut);

    for (auto& filter : allPassFilters)
        filter.process(context);

    filters[before].process(context);
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
    filters[after].process(context);
}

} // namespace xynth