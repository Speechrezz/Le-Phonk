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
    // TODO: This doesn't handle sample-rate changes, a race condition may occur

    buffer.resize(static_cast<size_t>(spec.sampleRate));
    workingBuffer.resize(spec.maximumBlockSize);

    writeAtomic.store(0, std::memory_order_release);
    read = 0;
}
void RingBuffer::writeSamples(juce::dsp::AudioBlock<float>& audioBlock)
{
    jassert(!buffer.empty() && !workingBuffer.empty()); // Call `prepare()`

    const size_t numChannels = audioBlock.getNumChannels();
    const size_t numSamples = audioBlock.getNumSamples();

    jassert(numChannels >= 1); // This thing better have channels

    // Mono the signal
    std::memcpy(workingBuffer.data(), audioBlock.getChannelPointer(0), sizeof(float) * numSamples);
    if (numChannels >= 2)
    {
        for (int i = 0; i < numSamples; ++i)
        {
            workingBuffer[i] += audioBlock.getSample(1, i);
            workingBuffer[i] *= 0.5f;
        }
    }

    // Push buffer
    size_t startIndex = writeAtomic.load(std::memory_order_acquire);

    if (startIndex + numSamples <= buffer.size())
    {
        std::memcpy(buffer.data() + startIndex, workingBuffer.data(), sizeof(float) * numSamples);
    }
    else
    {
        const size_t initialCount = buffer.size() - startIndex;
        const size_t remainingCount = numSamples - initialCount;

        std::memcpy(buffer.data() + startIndex, workingBuffer.data(), sizeof(float) * initialCount);
        std::memcpy(buffer.data(), workingBuffer.data() + initialCount, sizeof(float) * remainingCount);
    }

    writeAtomic.store((startIndex + numSamples) % buffer.size(), std::memory_order_release);
}

static float findMax(const float* buffer, size_t numSamples)
{
    using VecOps = juce::FloatVectorOperations;

    auto minAndMax = VecOps::findMinAndMax(buffer, numSamples);
    return std::max(std::abs(minAndMax.getStart()), minAndMax.getEnd());
}

float RingBuffer::readLoudestSample()
{
    size_t write = writeAtomic.load(std::memory_order_acquire);

    if (read == write)
        return -1.f;

    if (read < write)
    {
        const size_t numSamples = write - read;
        const float maxSample = findMax(buffer.data() + read, numSamples);

        read = write;
        return maxSample;
    }
    else // Wrap around
    {
        const size_t initialCount = buffer.size() - read;
        const size_t remainingCount = write;

        const float maxSample1 = findMax(buffer.data() + read, initialCount);
        const float maxSample2 = findMax(buffer.data(), remainingCount);

        read = write;
        return std::max(maxSample1, maxSample2);
    }
}

} // namespace xynth