/*
  ==============================================================================

    Dist3.h
    Created: 9 Sep 2022 9:39:35am
    Author:  thesp

  ==============================================================================
*/

#pragma once

#include "DistTemplate.h"

namespace xynth
{
    class Dist3 : public DistTemplate
    {
    public:
        Dist3();
        ~Dist3() = default;

        void prepare(const juce::dsp::ProcessSpec& spec) override;
        void process(juce::dsp::ProcessContextReplacing<float>& context) override;
        inline float distort(float sample) override { return sample; }

        void setAtomics(juce::AudioProcessorValueTreeState& treeState) override;

    private:
        void processAllPass(juce::dsp::ProcessContextReplacing<float>& context, int idx);

        juce::dsp::Gain<float> gainOut;
        juce::NormalisableRange<float> range;

        std::array<juce::dsp::ProcessorDuplicator<
            juce::dsp::IIR::Filter<float>,
            juce::dsp::IIR::Coefficients<float>>, 200> allPassFilters;

        std::atomic<float>* paramAtomic{ nullptr };

        int prevIdx{ 0 };

    };
} // namespace xynth