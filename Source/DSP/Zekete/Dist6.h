/*
  ==============================================================================

    Dist6.h
    Created: 10 Sep 2022 9:39:35am
    Author:  thesp

  ==============================================================================
*/

#pragma once

#include "DistTemplate.h"

namespace xynth
{
class Dist6 : public DistTemplate
{
public:
    Dist6();
    ~Dist6() = default;

    void prepare(const juce::dsp::ProcessSpec& spec) final;
    void process(juce::dsp::ProcessContextReplacing<float>& context) final;
    inline float distort(float sample, float param = 0.f) final
    { 
        const float dB = juce::jmap(param, 0.f, ZEKETE_MAX_DB);
        const float gain = juce::Decibels::decibelsToGain(dB);

        return shaper.functionToUse(sample * gain); 
    }

    inline float xAxis(float param) final
    {
        return juce::mapToLog10(param, 1.f, 0.3f);
    }

    void setAtomics(juce::AudioProcessorValueTreeState& treeState) final;

private:
    void processAllPass(juce::dsp::ProcessContextReplacing<float>& context);

    juce::dsp::WaveShaper<float> shaper;
    juce::dsp::Gain<float> gainIn, gainOut;

    std::array<juce::dsp::ProcessorDuplicator<
        juce::dsp::IIR::Filter<float>,
        juce::dsp::IIR::Coefficients<float>>, 3> filters;

    std::array<juce::dsp::ProcessorDuplicator<
        juce::dsp::IIR::Filter<float>,
        juce::dsp::IIR::Coefficients<float>>, 3> allPassFilters;

    std::atomic<float>* paramAtomic{ nullptr };

    enum FiltersEnum { before1, before2, after };
};
} // namespace xynth