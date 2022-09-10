/*
  ==============================================================================

    Bitcrush.h
    Created: 9 Sep 2022 7:05:04pm
    Author:  pwmag

  ==============================================================================
*/

#pragma once

#include "DistTemplate.h"
#include "WDYMShaper.h"

namespace xynth
{
    class WDYMBitcrush : public DistTemplate
    {
    public:
        WDYMBitcrush();
        ~WDYMBitcrush() = default;

        void prepare(const juce::dsp::ProcessSpec& spec) override;
        void process(juce::dsp::ProcessContextReplacing<float>& context) override;
        inline float distort(float x) override {
            float param = paramAtomic->load(std::memory_order_relaxed) * 0.01f;
            param = range.convertFrom0to1(param);

            x -= param;
            if (x < -1) {
                x = -(x + 1) - 1;
            }
            x += param;

            return std::min(x, 1.f);
        }

        void setAtomics(juce::AudioProcessorValueTreeState& treeState) override;

    private:

        void sampleAndHold(juce::dsp::ProcessContextReplacing<float>& context, float param);

        WDYMShaper<float> quantizer;
        juce::dsp::Gain<float> gainIn;
        juce::dsp::Gain<float> gainOut;
        juce::NormalisableRange<float> range;

        std::atomic<float>* paramAtomic{ nullptr };

        float prevParam{ 0 };

        std::vector<float> hold;

        float samplesToMs;
        unsigned int scanner = 0;

    };
} // namespace xynth