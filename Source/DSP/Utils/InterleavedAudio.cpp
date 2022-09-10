/*
  ==============================================================================

    InterleavedAudio.cpp
    Created: 10 Sep 2022 12:58:33pm
    Author:  thesp

  ==============================================================================
*/

#include "InterleavedAudio.h"

namespace xynth
{
void InterleavedAudio::prepare(const juce::dsp::ProcessSpec& spec)
{
    using namespace juce::dsp;
    interleaved = AudioBlock<SIMDRegister<float>>(interleavedBlockData, 1, spec.maximumBlockSize);

    zero = AudioBlock<float>(zeroData, SIMDRegister<float>::size(), spec.maximumBlockSize);
    zero.clear();
}
void InterleavedAudio::interleave(juce::dsp::ProcessContextReplacing<float>& context)
{
    using namespace juce;
    using namespace dsp;

    jassert(context.getInputBlock().getNumSamples()  == context.getOutputBlock().getNumSamples());
    jassert(context.getInputBlock().getNumChannels() == context.getOutputBlock().getNumChannels());

    const auto& input = context.getInputBlock();
    const auto numSamples = (int)input.getNumSamples();

    interleaved = AudioBlock<SIMDRegister<float>>(interleavedBlockData, 1, input.getNumSamples());
    zero = AudioBlock<float>(zeroData, SIMDRegister<float>::size(), input.getNumSamples());

    auto inChannels = prepareChannelPointers(input);

    using Format = AudioData::Format<AudioData::Float32, AudioData::NativeEndian>;

    AudioData::interleaveSamples(AudioData::NonInterleavedSource<Format> { inChannels.data(), registerSize, },
                                 AudioData::InterleavedDest<Format>      { toBasePointer(interleaved.getChannelPointer(0)), registerSize },
                                 numSamples);
}
void InterleavedAudio::deinterleave(juce::dsp::ProcessContextReplacing<float>& context)
{
    using namespace juce;
    using namespace dsp;
    using Format = AudioData::Format<AudioData::Float32, AudioData::NativeEndian>;

    const auto& input = context.getInputBlock();
    const auto numSamples = (int)input.getNumSamples();
    auto outChannels = prepareChannelPointers(context.getOutputBlock());

    AudioData::deinterleaveSamples(AudioData::InterleavedSource<Format>  { toBasePointer(interleaved.getChannelPointer(0)), registerSize },
                                   AudioData::NonInterleavedDest<Format> { outChannels.data(), registerSize },
                                   numSamples);
}
} // namespace xynth