/*
  ==============================================================================

    Zekete.cpp
    Created: 3 Sep 2022 11:27:40am
    Author:  thesp

  ==============================================================================
*/

#include "Zekete.h"
#include "../Common/Constants.h"

namespace xynth
{
Zekete::Zekete()
{

}
void Zekete::prepare(const juce::dsp::ProcessSpec& spec)
{
    for (auto* dist : distArray)
        dist->prepare(spec);

    // Mixer
    mixer.prepare(spec);
    mixer.setMixingRule(juce::dsp::DryWetMixingRule::linear);
}
void Zekete::process(juce::dsp::ProcessContextReplacing<float>& context)
{
    const int idx = int(selectAtomic->load(std::memory_order_relaxed));
    jassert(idx < distArray.size() && idx >= 0); // index out of range
    
    const float mix = mixAtomic->load(std::memory_order_relaxed) * 0.01f;
    mixer.setWetMixProportion(mix);
    mixer.pushDrySamples(context.getInputBlock());

    distArray[idx]->process(context);
    mixer.mixWetSamples(context.getOutputBlock());
}
void Zekete::setAtomics(juce::AudioProcessorValueTreeState& treeState)
{
    selectAtomic = treeState.getRawParameterValue(DIST_SELECT_ID);
    mixAtomic    = treeState.getRawParameterValue(ZEKETE_MIX_ID);

    for (auto* dist : distArray)
        dist->setAtomics(treeState);
}
} // namespace xynth