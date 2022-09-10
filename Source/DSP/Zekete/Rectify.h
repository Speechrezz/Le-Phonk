/*
  ==============================================================================

    Rectify.h
    Created: 10 Sep 2022 11:26:22am
    Author:  pwmag

  ==============================================================================
*/

#pragma once
#include "DistTemplate.h"
#include "WDYMShaper.h"

namespace xynth
{
    class WDYMRect : public DistTemplate
    {
    public:
        WDYMRect();
        ~WDYMRect() = default;

        void prepare(const juce::dsp::ProcessSpec& spec) override;
        void process(juce::dsp::ProcessContextReplacing<float>& context) override;
        inline float distort(float x) override {
            float rawParam = paramAtomic->load(std::memory_order_relaxed) * 0.01f;
            float param = rectRange.convertFrom0to1(rawParam);

            return rectifier.functionToUse(x, param);

            //const struct {
            //    float paramMax = 30.f;
            //    int tensionBase = 10;
            //    float vf = 0.7f;
            //    float vb = -12.f;
            //    float tanh1 = 0.7f;
            //} diode;

            //float s = tanh(x) * (diode.paramMax * param + 1);

            //float o1 = 0;
            //if (s > diode.vf) o1 = s - diode.vf;

            //float o2;
            //if (s > diode.vb) o2 = o1;
            //else o2 = 2 * s - 2 * diode.vb;

            //float o3 = o2 / (diode.paramMax * param * diode.tanh1 + 1);

            //x = std::max(o3, -1.f);
            //x = std::min(x, 1.f);

            //return x;
        }

        void setAtomics(juce::AudioProcessorValueTreeState& treeState) override;

    private:
        WDYMShaper<float> rectifier;
        juce::dsp::Gain<float> gainIn;
        juce::dsp::Gain<float> gainOut;
        juce::NormalisableRange<float> rectRange;

        std::atomic<float>* paramAtomic{ nullptr };

        float prevParam{ 0 };

    };
} // namespace xynth