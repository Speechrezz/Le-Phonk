/*
  ==============================================================================

    RingBuffer.h
    Created: 6 Sep 2022 3:33:30pm
    Author:  thesp

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

namespace xynth
{
class RingBuffer
{
public:
    RingBuffer() = default;
    ~RingBuffer() = default;

    void prepare(juce::dsp::ProcessSpec& spec);
    void writeSamples(juce::dsp::AudioBlock<float>& buffer);
    float readSamples();

private:
    std::vector<float> buffer;
    std::atomic<size_t> writeAtomic{ 0 };
    size_t read{ 0 };
};
} // namespace xynth