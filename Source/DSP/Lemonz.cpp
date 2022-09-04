/*
  ==============================================================================

    Lemonz.cpp
    Created: 3 Sep 2022 9:48:14am
    Author:  thesp

  ==============================================================================
*/

#include "Lemonz.h"
#include "../Common/Constants.h"

constexpr float limit = 2.f;
constexpr float limitInv = 1.f / limit;
constexpr float limitSqr = limitInv * limitInv;

namespace xynth
{
Lemonz::Lemonz()
{
    shaper.functionToUse = [](float x)
    {
        x = juce::jlimit(-limit, limit, x);
        return x / (1 + x * x * limitSqr);
    };
}
void Lemonz::prepare(const juce::dsp::ProcessSpec& spec)
{
    gain.prepare(spec);
    gain.setRampDurationSeconds(0.005);
    shaper.prepare(spec);
}
void Lemonz::process(juce::dsp::ProcessContextReplacing<float>& context)
{
    float dB = paramAtomic->load(std::memory_order_relaxed) * 0.01f;
    dB = juce::jmap(dB, 0.f, 12.f);
    gain.setGainDecibels(dB);

    gain.process(context);
    shaper.process(context);
}
void Lemonz::setAtomics(juce::AudioProcessorValueTreeState& treeState)
{
    paramAtomic = treeState.getRawParameterValue(LEMONZ_ID);
}
} // namespace xynth