/*
  ==============================================================================

    Lemonz.h
    Created: 3 Sep 2022 9:48:14am
    Author:  thesp

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

namespace xynth
{
class Fonz
{
public:
    Fonz();
    ~Fonz() = default;

    void prepare(const juce::dsp::ProcessSpec& spec);
    void process(juce::dsp::ProcessContextReplacing<float>& context);

    void setAtomics(juce::AudioProcessorValueTreeState& treeState);

private:
    juce::dsp::WaveShaper<float> shaper;
    juce::dsp::Gain<float> gainIn, gainOut;

    std::atomic<float>* paramAtomic{ nullptr }, *enableAtomic{ nullptr };

};
} // namespace xynth