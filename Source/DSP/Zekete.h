/*
  ==============================================================================

    Zekete.h
    Created: 3 Sep 2022 11:27:40am
    Author:  thesp

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Zekete/ZeketeHeader.h"

namespace xynth
{
class Zekete
{
public:
    Zekete();
    ~Zekete() = default;

    void prepare(const juce::dsp::ProcessSpec& spec);
    void process(juce::dsp::ProcessContextReplacing<float>& context);

    void setAtomics(juce::AudioProcessorValueTreeState& treeState);

private:
    Dist1 dist1;
    Dist2 dist2;
    Dist3 dist3;
    WDYMBitcrush bitcrusher;
    WDYMRect rectifier;
    std::atomic<float>* selectAtomic {nullptr};

public:
    std::array<DistTemplate*, 5> distArray{ &dist1, &dist2, &dist3, &bitcrusher, &rectifier };

};
} // namespace xynth