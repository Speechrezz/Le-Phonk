/*
  ==============================================================================

    OTTwithMultiplier.cpp
    Created: 13 Jan 2023 6:41:18pm
    Author:  thesp

  ==============================================================================
*/

#include "OTTwithMultiplier.h"
#include "PluginProcessor.h"

namespace xynth
{

OTTwithMultiplier::OTTwithMultiplier(LePhonkAudioProcessor& processor) :
    multiplierParam(*processor.treeState.getRawParameterValue(OTT_MULT_ID)),
    ottArray{
        OTT(processor),
        OTT(processor),
        OTT(processor),
        OTT(processor),
        OTT(processor),
    }
{}

void OTTwithMultiplier::reset() noexcept
{
    for (auto& ott : ottArray)
        ott.reset();
}

void OTTwithMultiplier::prepare(const juce::dsp::ProcessSpec& spec) noexcept
{
    for (auto& ott : ottArray)
        ott.prepare(spec);
}

void OTTwithMultiplier::process(juce::dsp::ProcessContextReplacing<float>& context) noexcept
{
    const auto multiplierAmount = static_cast<size_t>(multiplierParam.load(std::memory_order_relaxed));

    for (size_t i = 0; i < multiplierAmount; ++i)
    {
        auto& ott = ottArray[i];
        ott.process(context);
    }
}

} // namespace xynth