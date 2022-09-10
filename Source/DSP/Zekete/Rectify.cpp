/*
  ==============================================================================

    Rectify.cpp
    Created: 10 Sep 2022 11:26:22am
    Author:  pwmag

  ==============================================================================
*/

#include "Rectify.h"

namespace xynth
{
    WDYMRect::WDYMRect()
    {
        rectRange.setSkewForCentre(0.4f);
        
        rectifier.functionToUse = [](float x, float param) {
            const struct {
                float paramMax = 30.f;
                int tensionBase = 10;
                float vf = 0.7f;
                float vb = -12.f;
                float tanh1 = 0.7f;
            } diode;
            float dry = x;
            float s = tanh(x) * (diode.paramMax * param + 1);

            float o1 = 0;
            if (s > diode.vf) o1 = s - diode.vf;

            float o2;
            if (s > diode.vb) o2 = o1;
            else o2 = 2 * s - 2 * diode.vb;

            float o3 = o2 / (diode.paramMax * param * diode.tanh1 + 1);

            x = std::max(o3, -1.f);
            x = std::min(x, 1.f);

            if (param < 0.5) {
                x = (param * x) + (0.5 - param) * dry;
            }

            return x;
        };

    }
    void WDYMRect::prepare(const juce::dsp::ProcessSpec& spec)
    {

        gainIn.prepare(spec);
        gainIn.setRampDurationSeconds(0.01);
        gainIn.setGainDecibels(0);

        gainOut.prepare(spec);
        gainOut.setRampDurationSeconds(0.01);
        gainOut.setGainDecibels(0);

        rectifier.prepare(spec);
    }

    void WDYMRect::process(juce::dsp::ProcessContextReplacing<float>& context)
    {
        float rawParam = paramAtomic->load(std::memory_order_relaxed) * 0.01f;
        float rectParam = rectRange.convertFrom0to1(rawParam);

        gainIn.process(context);
        rectifier.process(context, rectParam);
        gainOut.process(context);
    }

    void WDYMRect::setAtomics(juce::AudioProcessorValueTreeState& treeState)
    {
        paramAtomic = treeState.getRawParameterValue(ZEKETE_ID);
    }
} // namespace xynth