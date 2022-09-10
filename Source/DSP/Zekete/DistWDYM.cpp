/*
  ==============================================================================

    DistWDYM.cpp
    Created: 9 Sep 2022 7:05:04pm
    Author:  pwmag

  ==============================================================================
*/

#include "DistWDYM.h"

namespace xynth
{
    DistWDYM::DistWDYM()
    {
        range.setSkewForCentre(0.05f);
        rectRange.setSkewForCentre(0.8f);
        samplesToMs = 0;

        rectifier.functionToUse = [](float x, float param) {

            x -= param;
            if (x < -1) {
                x = -(x + 1) - 1;
            }
            x += param;

            return x;
        };

        quantizer.functionToUse = [](float x, float param) {
            float ogx = x;
            if (param < 0.01) return x;

            int bitmagic = x * 32;
            bitmagic = (bitmagic << (int)(param * 32)) >> (int)(param * 32);
            x = (float)bitmagic / 32.0f;

            return (x + ogx) / 2;
        };

    }
    void DistWDYM::prepare(const juce::dsp::ProcessSpec& spec)
    {

        gainIn.prepare(spec);/*
        gainIn.setRampDurationSeconds(0.01);
        gainIn.setGainDecibels(0);

        gainOut.prepare(spec);
        gainOut.setRampDurationSeconds(0.01);
        gainOut.setGainDecibels(0);*/

        rectifier.prepare(spec);
        quantizer.prepare(spec);

        hold = std::vector<float>(spec.maximumBlockSize);
        samplesToMs = spec.sampleRate / 1000.0;
    }

    void DistWDYM::process(juce::dsp::ProcessContextReplacing<float>& context)
    {
        float rawParam = paramAtomic->load(std::memory_order_relaxed) * 0.01f;
        float param = range.convertFrom0to1(rawParam);
        float rectParam = rectRange.convertFrom0to1(rawParam);

        rectifier.process(context, rectParam);
        sampleAndHold(context, param);
        quantizer.process(context, param);
    }

    void DistWDYM::sampleAndHold(juce::dsp::ProcessContextReplacing<float>& context, float param) {
        juce::dsp::AudioBlock<const float> inBlock = context.getInputBlock();
        juce::dsp::AudioBlock<float> outBlock = context.getOutputBlock();


        auto len = inBlock.getNumSamples();
        auto numChans = inBlock.getNumChannels();
        std::vector<const float*> inSamples(numChans, 0);
        std::vector<float*> outSamples(numChans, 0);

        unsigned int holdLength = (int)(samplesToMs * param * 7) + 1;  // SaH interval of 1 sample to 7ms

        for (unsigned int c = 0; c < numChans; c++) {
            inSamples[c] = inBlock.getChannelPointer(c);
            outSamples[c] = outBlock.getChannelPointer(c);
			hold[c] = inSamples[c][0];
        }

        for (size_t i = 0; i < len; i++) {
            if (++scanner % holdLength == 0) {
                for (unsigned int c = 0; c < numChans; c++) {
                    hold[c] = inSamples[c][i];
                    outSamples[c][i] = inSamples[c][i];
                }
            }
            else {
                for (unsigned int c = 0; c < numChans; c++) {
                    outSamples[c][i] = hold[c];
                }
            }
        }
    }

    void DistWDYM::setAtomics(juce::AudioProcessorValueTreeState& treeState)
    {
        paramAtomic = treeState.getRawParameterValue(ZEKETE_ID);
    }
} // namespace xynth