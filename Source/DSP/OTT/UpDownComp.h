/*
  ==============================================================================

    MyCompressor.h
    Created: 30 Aug 2022 10:07:24am
    Author:  thesp

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

namespace xynth
{

struct CompParams
{
    float thresh   { 1.f };
    float invThresh{ 1.f };
    float invRatio { 1.f };
};

class UpDownComp {

public:
    UpDownComp() = default;
    ~UpDownComp() = default;

    void reset() noexcept;
    void prepare(const juce::dsp::ProcessSpec& spec) noexcept;
    void process(juce::dsp::ProcessContextReplacing<float>& context) noexcept;

    /// <summary>
    /// Updates the parameters in the compressor
    /// </summary>
    /// <param name="downThresh">- Downward threshold (in dB)</param>
    /// <param name="downRatio">- Downward ratio</param>
    /// <param name="upThresh">- Upward threshold (in dB)</param>
    /// <param name="upRatio">- Upward ratop</param>
    /// <param name="attack">- Attack time (in ms)</param>
    /// <param name="decay">- Decay time (in ms)</param>
    /// <param name="gain">- Output gain (in dB)</param>
    void update(float downThresh, float downRatio, float upThresh, float upRatio, 
        float attack, float decay, float gain) noexcept;

    /// <summary>
    /// Updates time-based parameters
    /// </summary>
    /// <param name="attack">- Attack time (in ms)</param>
    /// <param name="decay">- Decay time (in ms)</param>
    void updateTimes(float attack, float decay) noexcept;

    float processSample(int channel, float sample) noexcept;

private:
    juce::dsp::BallisticsFilter<float> envelope, spikeRemoverEnv;
    CompParams paramsDown, paramsUp;

    float outGain = 1.f;
};

} // namespace xynth