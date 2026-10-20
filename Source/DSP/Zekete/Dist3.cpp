/*
  ==============================================================================

    Dist3.cpp
    Created: 9 Sep 2022 9:39:35am
    Author:  thesp

  ==============================================================================
*/

#include "Dist3.h"

namespace xynth
{

Dist3::Dist3()
{
    range.setSkewForCentre(0.2f);
}

void Dist3::prepare(const juce::dsp::ProcessSpec& spec)
{
    float cutoff = 200.f;
    const float cutoffStep = 3.f;
    for (auto& filter : allPassFilters)
    {
        filter.prepare(spec);
        filter.updateParameters(cutoff);
        cutoff += cutoffStep;
    }

    interleaved.prepare(spec);
}

void Dist3::process(juce::dsp::ProcessContextReplacing<float>& context)
{
    const auto maxAmount = static_cast<float>(allPassFilters.size());

    float param = paramAtomic->load(std::memory_order_relaxed) * 0.01f;
    param = range.convertFrom0to1(param);
    const auto newAmount = static_cast<size_t>(juce::jmap(param, 0.f, maxAmount));

    interleaved.interleave(context);

    if (newAmount == prevAmount)
    {
        processAllPassUnchanged(context, newAmount);
    }
    else
    {
        processAllPassTransition(context, prevAmount, newAmount);
    }

    prevAmount = newAmount;
    interleaved.deinterleave(context);
}

void Dist3::setAtomics(juce::AudioProcessorValueTreeState& treeState)
{
    paramAtomic = treeState.getRawParameterValue(ZEKETE_ID);
}

void Dist3::processAllPassUnchanged(juce::dsp::ProcessContextReplacing<float>& context, size_t amount)
{
    jassert(amount <= allPassFilters.size());

    for (int i = 0; i < amount; ++i)
        allPassFilters[i].process(interleaved.getInterleavedAudio());
}

void Dist3::processAllPassTransition(juce::dsp::ProcessContextReplacing<float>& context, size_t prevAmount, size_t newAmount)
{
    jassert(newAmount <= allPassFilters.size());

    // TODO

    for (int i = 0; i < newAmount; ++i)
        allPassFilters[i].process(interleaved.getInterleavedAudio());
}

} // namespace xynth