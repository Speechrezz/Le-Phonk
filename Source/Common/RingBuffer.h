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

    // Call on audio thread
    void prepare(juce::dsp::ProcessSpec& spec);
    void writeSamples(juce::dsp::AudioBlock<float>& audioBlock);

    // Call on message/GUI thread
    float readLoudestSample();

private:
    std::vector<float> buffer, workingBuffer;
    std::atomic<size_t> writeAtomic{ 0 };

    size_t read{ 0 }; // GUI thread

};

} // namespace xynth