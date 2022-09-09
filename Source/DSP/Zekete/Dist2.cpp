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
Dist2::Dist2()
{
    shaper.functionToUse = [](float x)
    {
        //return 0.95f * std::tanh(x) + 0.05f * std::sin(x * 3.1416f);
        //return std::tanh(2.f * x * std::abs(x));
        const float sign = std::copysign(1.f, x);
        x = std::abs(x);
        if (x > 0.5f)
            x = 0.5f + (x - 0.5f) / (1.f + std::pow((x - 0.5f) * 2.f, 2.f));

        return sign * x * 1.3333333f;
    };
}
void Dist2::prepare(const juce::dsp::ProcessSpec& spec)
{
    gainIn.prepare(spec);
    gainIn.setRampDurationSeconds(0.005);

    gainOut.prepare(spec);
    gainOut.setRampDurationSeconds(0.005);

    shaper.prepare(spec);

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

void Dist2::process(juce::dsp::ProcessContextReplacing<float>& context)
{
    float dB = paramAtomic->load(std::memory_order_relaxed) * 0.01f;
    dB = juce::jmap(dB, 0.f, ZEKETE_MAX_DB);
    const float intensityIn = juce::Decibels::decibelsToGain(dB);
    gainIn.setGainLinear(intensityIn);

    const float avgGain = 0.22f;
    const float intensityOut = avgGain / distort(intensityIn * avgGain);
    gainOut.setGainLinear(intensityOut);
    //DBG("In: " << intensityIn << ", out: " << intensityOut);

    processAllPass(context);
    filters[before].process(context);
    gainIn.process(context);
    shaper.process(context);
    gainOut.process(context);
    filters[after].process(context);
}

void Dist2::setAtomics(juce::AudioProcessorValueTreeState& treeState)
{
    paramAtomic = treeState.getRawParameterValue(ZEKETE_ID);
}
void Dist2::processAllPass(juce::dsp::ProcessContextReplacing<float>& context)
{
    for (auto& filter : allPassFilters)
        filter.process(context);
}
} // namespace xynth