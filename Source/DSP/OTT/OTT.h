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

class LePhonkAudioProcessor;

namespace xynth
{

class OTT
{
public:
    OTT(LePhonkAudioProcessor&);
    ~OTT() = default;

    void reset() noexcept;
    void prepare(const juce::dsp::ProcessSpec& spec) noexcept;
    void process(juce::dsp::ProcessContextReplacing<float>& context) noexcept;

private:
    // Processes the two filters to create 24dB/oct slope
    void processFilter(juce::dsp::ProcessContextReplacing<float>& context, int filter) noexcept;

    std::atomic<float>& mixParam;
    std::atomic<float>& timeParam;
    std::atomic<float>& enableParam;

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