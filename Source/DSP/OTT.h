/*
  ==============================================================================

    OTT.h
    Created: 2 Sep 2022 3:42:08pm
    Author:  thesp

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "UpDownComp.h"

namespace xynth
{
class OTT
{
public:
    OTT() = default;
    ~OTT() = default;

    void setAtomics(juce::AudioProcessorValueTreeState& treeState);

    void prepare(const juce::dsp::ProcessSpec& spec);
    void process(juce::dsp::ProcessContextReplacing<float>& context);

private:
    void processFilter(juce::dsp::ProcessContextReplacing<float>& context, const int filter);

    std::atomic<float>* mixAtomic{ nullptr };

    std::array<UpDownComp, 3> comps;
    std::array<juce::AudioBuffer<float>, 3> buffers;
    std::array < juce::AudioBuffer<float>, 2> dryWetBuffers;

    juce::dsp::DryWetMixer<float> mixer;

    std::array<std::array<juce::dsp::ProcessorDuplicator<
        juce::dsp::IIR::Filter<float>, 
        juce::dsp::IIR::Coefficients<float>>, 4>, 2> filtersArray;

    enum CompsEnum  { low, mid, high };
    enum BuffersEnum{ dry, wet };
    enum FiltersEnum{ lowLowpass, midHighpass, midLowpass, highHighpass };
};
} // namespace xynth