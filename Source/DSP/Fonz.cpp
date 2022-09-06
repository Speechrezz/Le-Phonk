/*
  ==============================================================================

    Lemonz.cpp
    Created: 3 Sep 2022 9:48:14am
    Author:  thesp

  ==============================================================================
*/

#include "Fonz.h"
#include "../Common/Constants.h"

constexpr float limit = 2.f;
constexpr float limitInv = 1.f / limit;
constexpr float limitSqr = limitInv * limitInv;

namespace xynth
{
Fonz::Fonz()
{
    shaper.functionToUse = [](float x)
    {
        x = juce::jlimit(-limit, limit, x);
        return x / (1 + x * x * limitSqr);
    };
}
void Fonz::prepare(const juce::dsp::ProcessSpec& spec)
{
    gainIn.prepare(spec);
    gainIn.setRampDurationSeconds(0.005);

    gainOut.prepare(spec);
    gainOut.setRampDurationSeconds(0.005);

    shaper.prepare(spec);
}
void Fonz::process(juce::dsp::ProcessContextReplacing<float>& context)
{
    float dB = paramAtomic->load(std::memory_order_relaxed) * 0.01f;
    dB = juce::jmap(dB, 0.f, 18.f);
    gainIn.setGainDecibels(dB);
    gainOut.setGainDecibels(dB * -0.9f);

    gainIn.process(context);
    shaper.process(context);
    gainOut.process(context);
}
void Fonz::setAtomics(juce::AudioProcessorValueTreeState& treeState)
{
    paramAtomic = treeState.getRawParameterValue(FONZ_ID);
}
} // namespace xynth