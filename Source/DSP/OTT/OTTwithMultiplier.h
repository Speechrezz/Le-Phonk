/*
  ==============================================================================

    OTTwithMultiplier.h
    Created: 13 Jan 2023 6:41:18pm
    Author:  thesp

  ==============================================================================
*/

#pragma once
#include "OTT.h"
#include "Common/Constants.h"

class LePhonkAudioProcessor;

namespace xynth
{

class OTTwithMultiplier
{
public:
    OTTwithMultiplier(LePhonkAudioProcessor&);
    ~OTTwithMultiplier() = default;

    void reset() noexcept;
    void prepare(const juce::dsp::ProcessSpec& spec) noexcept;
    void process(juce::dsp::ProcessContextReplacing<float>& context) noexcept;

private:
    std::atomic<float>& multiplierParam;

    std::array<OTT, OTT_MULT_AMOUNT> ottArray;

};

} // namespace xynth