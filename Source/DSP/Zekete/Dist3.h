/*
  ==============================================================================

    Dist3.h
    Created: 9 Sep 2022 9:39:35am
    Author:  thesp

  ==============================================================================
*/

#pragma once

#include "DistortionProcessor.h"
#include "../Utils/SIMDFilter.h"
#include "../Utils/InterleavedAudio.h"

namespace xynth
{

class Dist3 : public DistortionProcessor
{
public:
    Dist3();
    ~Dist3() override = default;

    void reset() noexcept final;
    void prepare(const juce::dsp::ProcessSpec& spec) noexcept final;
    void process(juce::dsp::ProcessContextReplacing<float>& context, float zeketeAmount) noexcept final;

    // For visualization
    static float distortVisual(float x, float amount)
    { 
        float multX1 = x * (1.f + amount * 27.f);
        float multX2 = x * (2.f + amount * 10.f);
        float y = 0.4f * (std::abs(x) + 0.5f) * std::sin(multX1);
        y += 0.5f * x;
        y += 0.3f * std::sin(multX2 * std::sin(x * 8.7f));

        return juce::jmap(amount, x, y);
    }
    static float xAxis(float amount)
    { 
        return juce::mapToLog10(amount, 1.f, 0.5f);
    }

private:
    float computeAllPassAmount(float zeketeAmount) const noexcept;

    void processAllPassUnchanged() noexcept;
    void processAllPassTransition() noexcept;

    double sampleRate = -1.0;

    juce::NormalisableRange<float> range;

    std::array<SIMDFilter, 200> allPassFilters;
    InterleavedAudio interleaved;

    juce::LinearSmoothedValue<float> smoother;

    bool isTransitioning = false;

};

} // namespace xynth