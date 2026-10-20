/*
  ==============================================================================

    Dist6.cpp
    Created: 10 Sep 2022 9:39:35am
    Author:  thesp

  ==============================================================================
*/

#include "Dist6.h"

namespace xynth
{

void Dist6::reset() noexcept
{
    for (auto& filter : filters)
        filter.reset();

    for (auto& filter : allPassFilters)
        filter.reset();
}

void Dist6::prepare(const juce::dsp::ProcessSpec& spec) noexcept
{
    gainIn.prepare(spec);
    gainIn.setRampDurationSeconds(0.005);

    gainOut.prepare(spec);
    gainOut.setRampDurationSeconds(0.005);

    for (auto& filter : filters)
        filter.prepare(spec);

    *filters[before1].state = *juce::dsp::IIR::Coefficients<float>::makePeakFilter(spec.sampleRate, 150.f, 0.4f, 3.f);
    *filters[before2].state = *juce::dsp::IIR::Coefficients<float>::makeHighShelf (spec.sampleRate, 15000.f, 0.5f, 0.6f);
    *filters[after].state   = *juce::dsp::IIR::Coefficients<float>::makePeakFilter(spec.sampleRate, 150.f, 0.4f, 1.f / 3.f);

    float cutoff = 200.f;
    const float cutoffStep = 50.f;
    for (auto& filter : allPassFilters)
    {
        filter.prepare(spec);
        *filter.state = *juce::dsp::IIR::Coefficients<float>::makeAllPass(spec.sampleRate, cutoff);
        cutoff += cutoffStep;
    }
}

void Dist6::process(juce::dsp::ProcessContextReplacing<float>& context, float amount) noexcept
{
    const size_t numChannels = context.getInputBlock().getNumChannels();
    const size_t numSamples  = context.getInputBlock().getNumSamples();

    const float dB = juce::jmap(amount, 0.f, ZEKETE_MAX_DB);
    const float intensityIn = juce::Decibels::decibelsToGain(dB);
    gainIn.setGainLinear(intensityIn);

    const float avgGain = 0.18f;
    const float intensityOut = avgGain / std::min(intensityIn * avgGain, 1.f);
    gainOut.setGainLinear(intensityOut);

    for (auto& filter : allPassFilters)
        filter.process(context);

    filters[before1].process(context);
    filters[before2].process(context);
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