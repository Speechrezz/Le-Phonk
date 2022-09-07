/*
  ==============================================================================

    RingBuffer.cpp
    Created: 6 Sep 2022 3:33:30pm
    Author:  thesp

  ==============================================================================
*/

#include "RingBuffer.h"

namespace xynth
{
void RingBuffer::prepare(juce::dsp::ProcessSpec& spec)
{
    buffer.resize(spec.sampleRate);
    writeAtomic.store(0, std::memory_order_relaxed);
    read = 0;
}
void RingBuffer::writeSamples(juce::dsp::AudioBlock<float>& newBuffer)
{
    // Only works with 2 channels
    jassert(newBuffer.getNumChannels() == 2);
    size_t write = writeAtomic.load(std::memory_order_relaxed);

    const size_t numSamples = newBuffer.getNumSamples();
    const size_t limit = numSamples + write;
    auto channel1 = newBuffer.getChannelPointer(0);
    auto channel2 = newBuffer.getChannelPointer(1);

    // if samples fit within buffer
    if (limit < buffer.size())
    {
        size_t i = 0;
        for (size_t s = write; s < limit; ++s)
        {
            buffer[s] = (channel1[i] + channel2[i]) * 0.5f;
            ++i;
        }

        writeAtomic.store(limit % buffer.size(), std::memory_order_release);

        return;
    }
    
    // if samples go past buffer
    size_t i = 0;
    for (size_t s = write; s < buffer.size(); ++s)
    {
        buffer[s] = (channel1[i] + channel2[i]) * 0.5f;
        ++i;
    }

    const size_t newLimit = limit - buffer.size();

    for (size_t s = 0; s < newLimit; ++s)
    {
        buffer[s] = (channel1[i] + channel2[i]) * 0.5f;
        ++i;
    }

    writeAtomic.store(newLimit % buffer.size(), std::memory_order_release);
    return;
}
float RingBuffer::readSamples()
{
    size_t write = writeAtomic.load(std::memory_order_acquire);

    if (read == write) return 0.f;

    // If read is before write
    if (read < write)
    {
        float loudest = 0.f;

        for (read; read < write; ++read)
            loudest = std::max(std::abs(buffer[read]), loudest);

        return loudest;
    }

    // If read is NOT before write
    float loudest = 0.f;

    for (read; read < buffer.size(); ++read)
        loudest = std::max(std::abs(buffer[read]), loudest);

    for (read = 0; read < write; ++read)
        loudest = std::max(std::abs(buffer[read]), loudest);

    return loudest;
}
} // namespace xynth