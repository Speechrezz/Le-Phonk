/*
  ==============================================================================

    Dist3.cpp
    Created: 9 Sep 2022 9:39:35am
    Author:  thesp

  ==============================================================================
*/

#include "Dist3.h"

namespace xynth
{

Dist3::Dist3()
{
    range.setSkewForCentre(0.2f);
}

void Dist3::reset() noexcept
{
    for (auto& filter : allPassFilters)
        filter.reset();
}

void Dist3::prepare(const juce::dsp::ProcessSpec& spec) noexcept
{
    sampleRate = spec.sampleRate;

    constexpr float cutoffStep = 3.f;

    float cutoff = 200.f;
    for (auto& filter : allPassFilters)
    {
        filter.reset();
        filter.coeffs = juce::dsp::IIR::ArrayCoefficients<float>::makeAllPass(sampleRate, cutoff);

        cutoff += cutoffStep;
    }

    interleaved.prepare(spec);

    smoother.setCurrentAndTargetValue(smoother.getTargetValue());
    isTransitioning = false;
}

void Dist3::process(juce::dsp::ProcessContextReplacing<float>& context, float zeketeAmount) noexcept
{
    jassert(sampleRate > 0.0); // Call `prepare()`

    constexpr double secondsPerTransition = 0.001;
    const float newAmount = computeAllPassAmount(zeketeAmount);

    if (!isTransitioning && newAmount != smoother.getTargetValue())
    {
        const float prevAmount = smoother.getTargetValue();
        smoother.setCurrentAndTargetValue(prevAmount);

        const auto distance = static_cast<double>(std::abs(prevAmount - newAmount));
        smoother.reset(sampleRate, secondsPerTransition * distance);
        smoother.setTargetValue(newAmount);

        isTransitioning = true;
    }

    interleaved.interleave(context);

    if (!isTransitioning)
    {
        processAllPassUnchanged();
    }
    else
    {
        processAllPassTransition();
        isTransitioning = smoother.isSmoothing();
    }

    interleaved.deinterleave(context);
}

float Dist3::computeAllPassAmount(float zeketeAmount) const noexcept
{
    const auto maxAmount = static_cast<float>(allPassFilters.size());

    zeketeAmount = range.convertFrom0to1(zeketeAmount);
    return std::round(juce::jmap(zeketeAmount, 0.f, maxAmount));
}

void Dist3::processAllPassUnchanged() noexcept
{
    const auto amount = static_cast<size_t>(smoother.getTargetValue());
    jassert(amount <= allPassFilters.size());

    juce::dsp::ProcessContextReplacing context(interleaved.getInterleavedAudio());

    for (int i = 0; i < amount; ++i)
        allPassFilters[i].process(context);
}

void Dist3::processAllPassTransition() noexcept
{
    auto& interleavedBlock = interleaved.getInterleavedAudio();
    auto* interleavedChannel = interleavedBlock.getChannelPointer(0);
    const size_t numSamples = interleavedBlock.getNumSamples();

    for (size_t i = 0; i < numSamples; ++i)
    {
        const auto prevAmount = smoother.getCurrentValue();
        const auto amount = smoother.getNextValue();
        const auto amountLower = static_cast<size_t>(amount);
        const auto fraction = amount - std::floor(amount);

        for (size_t j = 0; j < amountLower; ++j)
            interleavedChannel[i] = allPassFilters[j].processSample(interleavedChannel[i]);

        if (amountLower < allPassFilters.size())
        {
            // Reset new filter
            if (std::floor(amount) > std::floor(prevAmount))
                allPassFilters[amountLower].reset();

            // Mix in new filter
            auto drySample = interleavedChannel[i];
            auto wetSample = allPassFilters[amountLower].processSample(drySample);
            interleavedChannel[i] =  drySample * (1.f - fraction) + wetSample * fraction;
        }
    }
}

} // namespace xynth