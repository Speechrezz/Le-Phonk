/*
  ==============================================================================

    Dist5.cpp
    Created: 10 Sep 2022 9:39:35am
    Author:  thesp

  ==============================================================================
*/

#include "Dist5.h"

constexpr float limit = 2.f;
constexpr float limitInv = 1.f / limit;
constexpr float limitSqr = limitInv * limitInv;

namespace xynth
{
Dist5::Dist5()
{
    shaper.functionToUse = [](float x)
    {
        //float y = std::sin(juce::jlimit(-1.f ,1.f ,x) * juce::MathConstants<float>::halfPi);
        //return y;
        x = juce::jlimit(-limit, limit, x);
        return x / (1 + x * x * limitSqr);
    };
}
void Dist5::prepare(const juce::dsp::ProcessSpec& spec)
{
    gainIn.prepare(spec);
    gainIn.setRampDurationSeconds(0.005);

    gainOut.prepare(spec);
    gainOut.setRampDurationSeconds(0.005);

    shaper.prepare(spec);

    for (auto& filter : filters)
        filter.prepare(spec);

    *filters[before1].state = *juce::dsp::IIR::Coefficients<float>::makePeakFilter(spec.sampleRate, 150.f, 0.4f, 2.f);
    *filters[before2].state = *juce::dsp::IIR::Coefficients<float>::makeHighShelf (spec.sampleRate, 15000.f, 0.5f, 0.6f);
    *filters[after].state   = *juce::dsp::IIR::Coefficients<float>::makePeakFilter(spec.sampleRate, 150.f, 0.4f, 1.f / 2.f);

    float cutoff = 200.f;
    const float cutoffStep = 40.f;
    for (auto& filter : allPassFilters)
    {
        filter.prepare(spec);
        *filter.state = *juce::dsp::IIR::Coefficients<float>::makeAllPass(spec.sampleRate, cutoff);
        cutoff += cutoffStep;
    }
}

void Dist5::process(juce::dsp::ProcessContextReplacing<float>& context)
{
    float param = paramAtomic->load(std::memory_order_relaxed) * 0.01f;
    float dB = juce::jmap(param, 0.f, ZEKETE_MAX_DB);
    const float intensityIn = juce::Decibels::decibelsToGain(dB);
    gainIn.setGainLinear(intensityIn);

    const float avgGain = 0.18f;
    const float intensityOut = avgGain / shaper.functionToUse(intensityIn * avgGain);
    gainOut.setGainLinear(intensityOut);
    //DBG("In: " << intensityIn << ", out: " << intensityOut);

    processAllPass(context);
    filters[before1].process(context);
    filters[before2].process(context);
    gainIn.process(context);
    shaper.process(context);
    gainOut.process(context);
    filters[after].process(context);
}

void Dist5::setAtomics(juce::AudioProcessorValueTreeState& treeState)
{
    paramAtomic = treeState.getRawParameterValue(ZEKETE_ID);
}
void Dist5::processAllPass(juce::dsp::ProcessContextReplacing<float>& context)
{
    for (auto& filter : allPassFilters)
        filter.process(context);
}
} // namespace xynth