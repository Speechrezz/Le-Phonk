/*
  ==============================================================================

    Bitcrush.cpp
    Created: 9 Sep 2022 7:05:04pm
    Author:  pwmag

  ==============================================================================
*/

#include "Bitcrush.h"

namespace xynth
{
    WDYMBitcrush::WDYMBitcrush()
    {
        range.setSkewForCentre(0.12f);
        samplesToMs = 0;

        quantizer.functionToUse = [](float x, float param) {
            float ogx = x;
            if (param < 0.01) return x;

            x = floor(x * (1 - param) * 100) / ((1 - param) * 100);

            return (x + ogx) / 2;
        };

    }
    void WDYMBitcrush::prepare(const juce::dsp::ProcessSpec& spec)
    {

        gainIn.prepare(spec);
        gainIn.setRampDurationSeconds(0.01);
        gainIn.setGainDecibels(0);

        gainOut.prepare(spec);
        gainOut.setRampDurationSeconds(0.01);
        gainOut.setGainDecibels(0);

        quantizer.prepare(spec);

        hold = std::vector<float>(spec.maximumBlockSize);
        samplesToMs = spec.sampleRate / 1000.0;
    }

    void WDYMBitcrush::process(juce::dsp::ProcessContextReplacing<float>& context)
    {
        float rawParam = paramAtomic->load(std::memory_order_relaxed) * 0.01f;
        float param = range.convertFrom0to1(rawParam);

        gainIn.process(context);

        sampleAndHold(context, param);
        quantizer.process(context, param);
        
        gainOut.process(context);
    }

    void WDYMBitcrush::sampleAndHold(juce::dsp::ProcessContextReplacing<float>& context, float param) {
        juce::dsp::AudioBlock<const float> inBlock = context.getInputBlock();
        juce::dsp::AudioBlock<float> outBlock = context.getOutputBlock();


        auto len = inBlock.getNumSamples();
        auto numChans = inBlock.getNumChannels();
        std::vector<const float*> inSamples(numChans, 0);
        std::vector<float*> outSamples(numChans, 0);

        unsigned int holdLength = (int)(samplesToMs * param * 20) + 1;  // SaH interval of 1 sample to 20ms

        if (param == 0 || param == 1) {
            return;
        }

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

    void WDYMBitcrush::setAtomics(juce::AudioProcessorValueTreeState& treeState)
    {
        paramAtomic = treeState.getRawParameterValue(ZEKETE_ID);
    }
} // namespace xynth