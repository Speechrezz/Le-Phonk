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
class Lemonz
{
public:
    Lemonz();
    ~Lemonz() = default;

    void prepare(const juce::dsp::ProcessSpec& spec);
    void process(juce::dsp::ProcessContextReplacing<float>& context);

    void setAtomics(juce::AudioProcessorValueTreeState& treeState);

private:
    juce::dsp::WaveShaper<float> shaper;
    juce::dsp::Gain<float> gainIn, gainOut;

    std::atomic<float>* paramAtomic{ nullptr };

};
} // namespace xynth