/*
  ==============================================================================

    Dist3.h
    Created: 9 Sep 2022 9:39:35am
    Author:  thesp

  ==============================================================================
*/

#pragma once

#include "DistTemplate.h"
#include "../Utils/SIMDFilter.h"
#include "../Utils/InterleavedAudio.h"

namespace xynth
{
class Dist3 : public DistTemplate
{
public:
    Dist3();
    ~Dist3() = default;

    void prepare(const juce::dsp::ProcessSpec& spec) override;
    void process(juce::dsp::ProcessContextReplacing<float>& context) override;
    inline float distort(float x, float param = 0.f) override
    { 
        float multX1 = x * (1.f + param * 27.f);
        float multX2 = x * (2.f + param * 10.f);
        float y = 0.4f * (std::abs(x) + 0.5f) * std::sin(multX1);
        y += 0.5f * x;
        y += 0.3f * std::sin(multX2 * std::sin(x * 8.7f));

        return juce::jmap(param, x, y);
    }

    inline float xAxis(float param) override
    { 
        return juce::mapToLog10(param, 1.f, 0.5f);
    }


    void setAtomics(juce::AudioProcessorValueTreeState& treeState) override;

private:
    void processAllPass(juce::dsp::ProcessContextReplacing<float>& context, int idx);

    juce::dsp::Gain<float> gainOut;
    juce::NormalisableRange<float> range;

    /*std::array<juce::dsp::ProcessorDuplicator<
        juce::dsp::IIR::Filter<float>,
        juce::dsp::IIR::Coefficients<float>>, 200> allPassFilters;*/

    std::array<xynth::SIMDFilter, 200> allPassFilters;
    xynth::InterleavedAudio inter;

    std::atomic<float>* paramAtomic{ nullptr };

    int prevIdx{ 0 };

};
} // namespace xynth