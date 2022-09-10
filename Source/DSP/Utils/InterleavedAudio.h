/*
  ==============================================================================

    InterleavedAudio.h
    Created: 10 Sep 2022 12:58:33pm
    Author:  thesp

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

constexpr auto registerSize = juce::dsp::SIMDRegister<float>::size();

namespace xynth
{
class InterleavedAudio
{
public:
    InterleavedAudio() = default;
    ~InterleavedAudio() = default;

    void prepare(const juce::dsp::ProcessSpec& spec);
    void interleave(juce::dsp::ProcessContextReplacing<float>& context);
    void deinterleave(juce::dsp::ProcessContextReplacing<float>& context);

    inline juce::dsp::AudioBlock<juce::dsp::SIMDRegister<float>>& getInterleavedAudio()
    {
        return interleaved;
    }

private:
    template <typename SampleType>
    std::array<SampleType*, registerSize> prepareChannelPointers(const juce::dsp::AudioBlock<SampleType>& block)
    {
        std::array<SampleType*, registerSize> result{};

        for (size_t ch = 0; ch < result.size(); ++ch)
            result[ch] = (ch < block.getNumChannels() ? block.getChannelPointer(ch) : zero.getChannelPointer(ch));

        return result;
    }

    template <typename T>
    static T* toBasePointer(juce::dsp::SIMDRegister<T>* r) noexcept
    {
        return reinterpret_cast<T*> (r);
    }

    juce::dsp::AudioBlock<juce::dsp::SIMDRegister<float>> interleaved;
    juce::dsp::AudioBlock<float> zero;

    juce::HeapBlock<char> interleavedBlockData, zeroData;

};
} // namespace xynth