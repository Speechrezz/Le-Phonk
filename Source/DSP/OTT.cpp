/*
  ==============================================================================

    OTT.cpp
    Created: 2 Sep 2022 3:42:08pm
    Author:  thesp

  ==============================================================================
*/

#include "OTT.h"
#include "../Common/Constants.h"

#define HIGH_CROSS 2500.f
#define LOW_CROSS 88.3f
#define Q 0.7071

namespace xynth
{

void OTT::setAtomics(juce::AudioProcessorValueTreeState& treeState)
{
    mixAtomic = treeState.getRawParameterValue(OTT_ID);
}

void OTT::prepare(const juce::dsp::ProcessSpec& spec)
{
    // Prepare the compressors
    for (auto& comp : comps)
        comp.prepare(spec);

    comps[high].update(-35.5f, 999.f, -40.8f, 4.17f, 13.5f, 132.f, 14.9f);
    comps[mid].update (-30.2f, 66.7f, -41.8f, 4.17f, 22.4f, 282.f, 12.5f);
    comps[low].update (-33.8f, 66.7f, -40.8f, 4.17f, 47.8f, 282.f, 14.3f);

    // Prepare the filters
    for (auto& filters : filtersArray)
    {
        for (auto& filter : filters)
            filter.prepare(spec);

        *filters[lowLowpass].state   = *juce::dsp::IIR::Coefficients<float>::makeLowPass (spec.sampleRate, LOW_CROSS,  Q);

        *filters[midHighpass].state  = *juce::dsp::IIR::Coefficients<float>::makeHighPass(spec.sampleRate, LOW_CROSS,  Q);
        *filters[midLowpass].state   = *juce::dsp::IIR::Coefficients<float>::makeLowPass (spec.sampleRate, HIGH_CROSS, Q);

        *filters[highHighpass].state = *juce::dsp::IIR::Coefficients<float>::makeHighPass(spec.sampleRate, HIGH_CROSS, Q);
    }

    // Prepare the buffers
    for (auto& buffer : buffers)
        buffer.setSize(spec.numChannels, spec.maximumBlockSize);
    for (auto& buffer : dryWetBuffers)
        buffer.setSize(spec.numChannels, spec.maximumBlockSize);

    // Mixer
    mixer.prepare(spec);
    mixer.setMixingRule(juce::dsp::DryWetMixingRule::linear);
}

void OTT::process(juce::dsp::ProcessContextReplacing<float>& context)
{
    // Setup basics
    const float mix = mixAtomic->load(std::memory_order_relaxed);

    const auto& inputBlock = context.getInputBlock();
    auto& outputBlock = context.getOutputBlock();
    const auto numChannels = outputBlock.getNumChannels();
    const auto numSamples = outputBlock.getNumSamples();

    dryWetBuffers[dry].clear();
    dryWetBuffers[wet].clear();
    auto blockDry = juce::dsp::AudioBlock<float>(dryWetBuffers[dry]).getSubBlock(0, numSamples);
    auto contextDry = juce::dsp::ProcessContextReplacing<float>(blockDry);
    auto blockWet = juce::dsp::AudioBlock<float>(dryWetBuffers[wet]).getSubBlock(0, numSamples);
    auto contextWet = juce::dsp::ProcessContextReplacing<float>(blockWet);

    // Copy buffers
    for (auto& buffer : buffers)
        for (size_t ch = 0; ch < numChannels; ++ch)
            buffer.copyFrom(ch, 0, inputBlock.getChannelPointer(ch), numSamples);

    // Low band
    auto blockLow = juce::dsp::AudioBlock<float>(buffers[low]).getSubBlock(0, numSamples);
    auto contextLow = juce::dsp::ProcessContextReplacing<float>(blockLow);
    processFilter(contextLow, lowLowpass);
    blockDry.add(blockLow);
    comps[low].process(contextLow);
    blockWet.add(blockLow);

    // Mid band
    auto blockMid = juce::dsp::AudioBlock<float>(buffers[mid]).getSubBlock(0, numSamples);
    auto contextMid = juce::dsp::ProcessContextReplacing<float>(blockMid);
    processFilter(contextMid, midHighpass);
    processFilter(contextMid, midLowpass);
    blockDry.add(blockMid);
    comps[mid].process(contextMid);
    blockWet.add(blockMid);

    // High band
    auto blockHigh = juce::dsp::AudioBlock<float>(buffers[high]).getSubBlock(0, numSamples);
    auto contextHigh = juce::dsp::ProcessContextReplacing<float>(blockHigh);
    processFilter(contextHigh, highHighpass);
    blockDry.add(blockHigh);
    comps[high].process(contextHigh);
    blockWet.add(blockHigh);

    mixer.setWetMixProportion(mix * 0.01f);
    mixer.pushDrySamples(blockDry);
    mixer.mixWetSamples(blockWet);
    context.getOutputBlock().copyFrom(blockWet);
}

void OTT::processFilter(juce::dsp::ProcessContextReplacing<float>& context, const int filter)
{
    filtersArray[0][filter].process(context);
    filtersArray[1][filter].process(context);
}

} // namespace xynth