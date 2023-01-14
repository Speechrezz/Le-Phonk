/*
  ==============================================================================

    OTTwithMultiplier.h
    Created: 13 Jan 2023 6:41:18pm
    Author:  thesp

  ==============================================================================
*/

#pragma once
#include "OTT.h"
#include "../../Common/Constants.h"

namespace xynth
{
class OTTwithMultiplier
{
public:
    OTTwithMultiplier() = default;
    ~OTTwithMultiplier() = default;

    void setAtomics(juce::AudioProcessorValueTreeState& treeState);

    void prepare(const juce::dsp::ProcessSpec& spec);
    void process(juce::dsp::ProcessContextReplacing<float>& context);

private:
    std::atomic<float>* multiplierAtomic{ nullptr };

    std::array<xynth::OTT, OTT_MULT_AMOUNT> ottArray;

};

} // namespace xynth