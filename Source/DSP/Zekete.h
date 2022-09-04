/*
  ==============================================================================

    Zekete.h
    Created: 3 Sep 2022 11:27:40am
    Author:  thesp

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

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
    juce::dsp::WaveShaper<float> shaper;
    juce::dsp::Gain<float> gainIn, gainOut;

    std::array<juce::dsp::ProcessorDuplicator<
        juce::dsp::IIR::Filter<float>,
        juce::dsp::IIR::Coefficients<float>>, 2> filters;

    std::atomic<float>* paramAtomic{ nullptr };

    enum FiltersEnum{ before, after };
};
} // namespace xynth