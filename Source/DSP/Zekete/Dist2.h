/*
  ==============================================================================

    Dist2.h
    Created: 9 Sep 2022 9:39:35am
    Author:  thesp

  ==============================================================================
*/

#pragma once

#include "DistTemplate.h"

namespace xynth
{
class Dist2 : public DistTemplate
{
public:
    Dist2();
    ~Dist2() = default;

    void prepare(const juce::dsp::ProcessSpec& spec) override;
    void process(juce::dsp::ProcessContextReplacing<float>& context) override;
    inline float distort(float sample, float param = 0.f) override
    { 
        const float dB = juce::jmap(param, 0.f, ZEKETE_MAX_DB);
        const float gain = juce::Decibels::decibelsToGain(dB);

        return shaper.functionToUse(sample * gain);
    }

    inline float xAxis(float param) override
    {
        return juce::mapToLog10(param, 1.f, 0.3f);
    }

    void setAtomics(juce::AudioProcessorValueTreeState& treeState) override;

private:
    void processAllPass(juce::dsp::ProcessContextReplacing<float>& context);

    juce::dsp::WaveShaper<float> shaper;
    juce::dsp::Gain<float> gainIn, gainOut;

    std::array<juce::dsp::ProcessorDuplicator<
        juce::dsp::IIR::Filter<float>,
        juce::dsp::IIR::Coefficients<float>>, 2> filters;

    std::array<juce::dsp::ProcessorDuplicator<
        juce::dsp::IIR::Filter<float>,
        juce::dsp::IIR::Coefficients<float>>, 6> allPassFilters;

    std::atomic<float>* paramAtomic{ nullptr };

    enum FiltersEnum { before, after };
};
} // namespace xynth