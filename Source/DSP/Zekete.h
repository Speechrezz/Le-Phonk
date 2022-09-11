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
    juce::dsp::DryWetMixer<float> mixer;

    Dist1 dist1;
    Dist2 dist2;
    Dist3 dist3;
    Dist4 dist4;
    Dist5 dist5;
    Dist6 dist6;
    std::atomic<float>* selectAtomic{ nullptr };
    std::atomic<float>* mixAtomic    {nullptr};

public:
    std::array<DistTemplate*, 6> distArray{ &dist1, &dist2, &dist3, &dist4, &dist5, &dist6 };

};
} // namespace xynth