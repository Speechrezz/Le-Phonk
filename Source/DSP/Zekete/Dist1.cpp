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
Dist1::Dist1()
{
    shaper.functionToUse = [](float x)
    {
        return std::tanh(x);
    };
}
void Dist1::prepare(const juce::dsp::ProcessSpec& spec)
{
    gainIn.prepare(spec);
    gainIn.setRampDurationSeconds(0.005);

    gainOut.prepare(spec);
    gainOut.setRampDurationSeconds(0.005);

    shaper.prepare(spec);

    for (auto& filter : filters)
        filter.prepare(spec);

    *filters[before].state = *juce::dsp::IIR::Coefficients<float>::makePeakFilter(spec.sampleRate, 555.f, 1.2f, 4.f);
    *filters[after].state = *juce::dsp::IIR::Coefficients<float>::makePeakFilter(spec.sampleRate, 555.f, 1.2f, 1.f / 4.f);
}

void Dist1::process(juce::dsp::ProcessContextReplacing<float>& context)
{
    float dB = paramAtomic->load(std::memory_order_relaxed) * 0.01f;
    dB = juce::jmap(dB, 0.f, ZEKETE_MAX_DB);
    const float intensityIn = juce::Decibels::decibelsToGain(dB);
    gainIn.setGainLinear(intensityIn);

    const float avgGain = 0.22f;
    const float intensityOut = avgGain / distort(intensityIn * avgGain);
    gainOut.setGainLinear(intensityOut);
    //DBG("In: " << intensityIn << ", out: " << intensityOut);

    filters[before].process(context);
    gainIn.process(context);
    shaper.process(context);
    gainOut.process(context);
    filters[after].process(context);
}

void Dist1::setAtomics(juce::AudioProcessorValueTreeState& treeState)
{
    paramAtomic = treeState.getRawParameterValue(ZEKETE_ID);
}
} // namespace xynth