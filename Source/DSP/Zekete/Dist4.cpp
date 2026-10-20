/*
  ==============================================================================

    Dist4.cpp
    Created: 10 Sep 2022 9:39:35am
    Author:  thesp

  ==============================================================================
*/

#include "Dist4.h"

namespace xynth
{

void Dist4::reset() noexcept
{
    for (auto& filter : filters)
        filter.reset();
}

void Dist4::prepare(const juce::dsp::ProcessSpec& spec) noexcept
{
    gainIn.prepare(spec);
    gainIn.setRampDurationSeconds(0.005);

    gainOut.prepare(spec);
    gainOut.setRampDurationSeconds(0.005);

    for (auto& filter : filters)
        filter.prepare(spec);

    *filters[before].state = *juce::dsp::IIR::Coefficients<float>::makePeakFilter(spec.sampleRate, 100.f, 0.3f, 2.f);
    *filters[after].state  = *juce::dsp::IIR::Coefficients<float>::makePeakFilter(spec.sampleRate, 100.f, 0.3f, 1.f / 2.f);
}

void Dist4::process(juce::dsp::ProcessContextReplacing<float>& context, float amount) noexcept
{
    const size_t numChannels = context.getInputBlock().getNumChannels();
    const size_t numSamples  = context.getInputBlock().getNumSamples();

    const float dB = juce::jmap(amount, 0.f, ZEKETE_MAX_DB);
    const float intensityIn = juce::Decibels::decibelsToGain(dB);
    gainIn.setGainLinear(intensityIn);

    const float intensityOut = juce::mapToLog10(amount, 0.6f, 0.2f);
    gainOut.setGainLinear(intensityOut);

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