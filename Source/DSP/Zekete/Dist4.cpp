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
Dist4::Dist4()
{
    shaper.functionToUse = [](float x)
    {
        float y = 1.f / (std::abs(x) + 1.f) * std::sin(x * juce::MathConstants<float>::halfPi);
        return y + std::tanh(x * 0.2f);
    };
}
void Dist4::prepare(const juce::dsp::ProcessSpec& spec)
{
    gainIn.prepare(spec);
    gainIn.setRampDurationSeconds(0.005);

    gainOut.prepare(spec);
    gainOut.setRampDurationSeconds(0.005);

    shaper.prepare(spec);

    for (auto& filter : filters)
        filter.prepare(spec);

    *filters[before].state = *juce::dsp::IIR::Coefficients<float>::makePeakFilter(spec.sampleRate, 100.f, 0.3f, 2.f);
    *filters[after].state  = *juce::dsp::IIR::Coefficients<float>::makePeakFilter(spec.sampleRate, 100.f, 0.3f, 1.f / 2.f);
}

void Dist4::process(juce::dsp::ProcessContextReplacing<float>& context)
{
    float param = paramAtomic->load(std::memory_order_relaxed) * 0.01f;
    float dB = juce::jmap(param, 0.f, ZEKETE_MAX_DB);
    const float intensityIn = juce::Decibels::decibelsToGain(dB);
    gainIn.setGainLinear(intensityIn);

    const float avgGain = 0.2f;
    const float intensityOut = juce::mapToLog10(param, 0.6f, 0.2f);
    gainOut.setGainLinear(intensityOut);
    //DBG("In: " << intensityIn << ", out: " << intensityOut);

    filters[before].process(context);
    gainIn.process(context);
    shaper.process(context);
    gainOut.process(context);
    filters[after].process(context);
}

void Dist4::setAtomics(juce::AudioProcessorValueTreeState& treeState)
{
    paramAtomic = treeState.getRawParameterValue(ZEKETE_ID);
}
} // namespace xynth