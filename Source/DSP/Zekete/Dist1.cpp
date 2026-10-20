/*
  ==============================================================================

    Dist1.cpp
    Created: 9 Sep 2022 9:39:35am
    Author:  thesp

  ==============================================================================
*/

#include "Dist1.h"

namespace xynth
{

void Dist1::reset() noexcept
{
    for (auto& filter : filters)
        filter.reset();
}

void Dist1::prepare(const juce::dsp::ProcessSpec& spec) noexcept
{
    gainIn.prepare(spec);
    gainIn.setRampDurationSeconds(0.005);

    gainOut.prepare(spec);
    gainOut.setRampDurationSeconds(0.005);

    for (auto& filter : filters)
        filter.prepare(spec);

    *filters[before].state = *juce::dsp::IIR::Coefficients<float>::makePeakFilter(spec.sampleRate, 555.f, 1.2f, 4.f);
    *filters[after].state = *juce::dsp::IIR::Coefficients<float>::makePeakFilter(spec.sampleRate, 555.f, 1.2f, 1.f / 4.f);
}

void Dist1::process(juce::dsp::ProcessContextReplacing<float>& context, float amount) noexcept
{
    const size_t numChannels = context.getInputBlock().getNumChannels();
    const size_t numSamples  = context.getInputBlock().getNumSamples();

    const float dB = juce::jmap(amount, 0.f, ZEKETE_MAX_DB);
    const float intensityIn = juce::Decibels::decibelsToGain(dB);
    gainIn.setGainLinear(intensityIn);

    constexpr float avgGain = 0.2f;
    const float intensityOut = avgGain / distortSample(intensityIn * avgGain);
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