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
    inline float distort(float x) override 
    { 
        const float sign = std::copysign(1.f, x);
        x = std::abs(x);
        if (x > 0.5f)
            x = 0.5f + (x - 0.5f) / (1.f + std::pow((x - 0.5f) * 2.f, 2.f));

        return sign * x * 1.3333333f;
    }

    void setAtomics(juce::AudioProcessorValueTreeState& treeState) override;

private:
    juce::dsp::WaveShaper<float> shaper;
    juce::dsp::Gain<float> gainIn, gainOut;

    std::array<juce::dsp::ProcessorDuplicator<
        juce::dsp::IIR::Filter<float>,
        juce::dsp::IIR::Coefficients<float>>, 2> filters;

    std::atomic<float>* paramAtomic{ nullptr };

    enum FiltersEnum { before, after };
};
} // namespace xynth