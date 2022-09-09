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
}
void Zekete::process(juce::dsp::ProcessContextReplacing<float>& context)
{
    const int idx = int(selectAtomic->load(std::memory_order_relaxed));
    jassert(idx < distArray.size() && idx >= 0); // index out of range

    distArray[idx]->process(context);
}
void Zekete::setAtomics(juce::AudioProcessorValueTreeState& treeState)
{
    selectAtomic = treeState.getRawParameterValue(DIST_SELECT_ID);

    for (auto* dist : distArray)
        dist->setAtomics(treeState);
}
} // namespace xynth