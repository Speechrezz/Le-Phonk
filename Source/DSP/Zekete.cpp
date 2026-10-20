/*
  ==============================================================================

    Zekete.cpp
    Created: 3 Sep 2022 11:27:40am
    Author:  thesp

  ==============================================================================
*/

#include "Zekete.h"
#include "../Common/Constants.h"
#include "../PluginProcessor.h"

namespace xynth
{

Zekete::Zekete(LePhonkAudioProcessor& processor) :
    distTypeParam(*processor.treeState.getRawParameterValue(DIST_SELECT_ID)),
    mixParam(*processor.treeState.getRawParameterValue(ZEKETE_MIX_ID)),
    amountParam(*processor.treeState.getRawParameterValue(ZEKETE_ID))
{
    distortion = distortionFromType(0);
}

void Zekete::reset() noexcept
{
    distortion->reset();
}

void Zekete::prepare(const juce::dsp::ProcessSpec& newSpec) noexcept
{
    spec = newSpec;

    distortion->prepare(spec);

    mixer.prepare(spec);
    mixer.setMixingRule(juce::dsp::DryWetMixingRule::sin3dB);
}

void Zekete::process(juce::dsp::ProcessContextReplacing<float>& context) noexcept
{
    const auto newDistType = static_cast<size_t>(distTypeParam.load(std::memory_order_relaxed));
    if (newDistType != distType)
    {
        distType = newDistType;
        distortion = distortionFromType(distType);
        distortion->prepare(spec);
    }

    const float mix = mixParam.load(std::memory_order_relaxed) * 0.01f;
    mixer.setWetMixProportion(mix);
    mixer.pushDrySamples(context.getInputBlock());

    const float amount = 0.01f * amountParam.load(std::memory_order_relaxed);
    distortion->process(context, amount);
    mixer.mixWetSamples(context.getOutputBlock());
}

} // namespace xynth