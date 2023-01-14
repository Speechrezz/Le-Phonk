/*
  ==============================================================================

    OTTwithMultiplier.cpp
    Created: 13 Jan 2023 6:41:18pm
    Author:  thesp

  ==============================================================================
*/

#include "OTTwithMultiplier.h"

namespace xynth
{
void OTTwithMultiplier::setAtomics(juce::AudioProcessorValueTreeState& treeState)
{
    for (auto& ott : ottArray)
        ott.setAtomics(treeState);

    multiplierAtomic = treeState.getRawParameterValue(OTT_MULT_ID);
}

void OTTwithMultiplier::prepare(const juce::dsp::ProcessSpec& spec)
{
    for (auto& ott : ottArray)
        ott.prepare(spec);
}

void OTTwithMultiplier::process(juce::dsp::ProcessContextReplacing<float>& context)
{
    const int multiplierAmount = (int)multiplierAtomic->load(std::memory_order_relaxed);

    for (int i = 0; i < multiplierAmount; ++i)
    {
        auto& ott = ottArray[i];
        ott.process(context);
    }
}
} // namespace xynth