/*
  ==============================================================================

    WDYMShaper.h
    Created: 10 Sep 2022 11:32:17am
    Author:  pwmag

  ==============================================================================
*/

#pragma once
namespace xynth {
    template <typename FloatType, typename Function = FloatType(*) (FloatType, FloatType)>
    class WDYMShaper : public juce::dsp::WaveShaper<FloatType, Function> {
    public:

        template <typename SampleType>
        SampleType JUCE_VECTOR_CALLTYPE processSample(SampleType inputSample) const noexcept
        {
            return functionToUse(inputSample, param);
        }

        template <typename ProcessContext>
        void process(const ProcessContext& context, FloatType param) const noexcept {
            if (context.isBypassed)
            {
                if (context.usesSeparateInputAndOutputBlocks())
                    context.getOutputBlock().copyFrom(context.getInputBlock());
            }
            else
            {
                juce::dsp::AudioBlock<const float> inBlock = context.getInputBlock();
                juce::dsp::AudioBlock<float> outBlock = context.getOutputBlock();
                auto len = inBlock.getNumSamples();
                auto numChans = inBlock.getNumChannels();

                for (unsigned int c = 0; c < numChans; c++) {
                    auto inSamples = inBlock.getChannelPointer(c);
                    auto outSamples = outBlock.getChannelPointer(c);

                    for (unsigned int i = 0; i < len; i++) {
                        outSamples[i] = functionToUse(inSamples[i], param);
                    }
                }
            }
        }
    };
}