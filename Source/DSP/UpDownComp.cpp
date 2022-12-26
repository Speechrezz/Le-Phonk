/*
  ==============================================================================

    MyCompressor.cpp
    Created: 30 Aug 2022 10:07:24am
    Author:  thesp

  ==============================================================================
*/

#include "UpDownComp.h"
#include "../Common/Constants.h"

constexpr float loudnessCutoff = 0.000015849f; // -96 dB

namespace xynth
{
void UpDownComp::prepare(const juce::dsp::ProcessSpec& spec)
{
    envelope.prepare(spec);
    envelope.setLevelCalculationType(juce::dsp::BallisticsFilterLevelCalculationType::RMS);

    spikeRemoverEnv.prepare(spec);
    spikeRemoverEnv.setLevelCalculationType(juce::dsp::BallisticsFilterLevelCalculationType::RMS);
}

void UpDownComp::process(juce::dsp::ProcessContextReplacing<float>& context)
{
    const auto& inputBlock = context.getInputBlock();
    auto& outputBlock = context.getOutputBlock();
    const auto numChannels = outputBlock.getNumChannels();
    const auto numSamples = outputBlock.getNumSamples();

    for (int channel = 0; channel < numChannels; ++channel)
    {
        auto* inputSamples = inputBlock.getChannelPointer(channel);
        auto* outputSamples = outputBlock.getChannelPointer(channel);

        for (size_t i = 0; i < numSamples; ++i)
            outputSamples[i] = processSample(channel, inputSamples[i]);
    }
}

void UpDownComp::update(float downThresh, float downRatio, float upThresh, float upRatio, 
    float attack, float decay, float gain)
{
    paramsDown.thresh    = juce::Decibels::decibelsToGain(downThresh);
    paramsDown.invThresh = 1.f / paramsDown.thresh;
    paramsDown.invRatio  = 1.f / downRatio;

    paramsUp.thresh = juce::Decibels::decibelsToGain(upThresh);
    paramsUp.invThresh = 1.f / paramsUp.thresh;
    paramsUp.invRatio = 1.f / upRatio;

    envelope.setAttackTime (attack * 0.5f);
    envelope.setReleaseTime(decay);

    spikeRemoverEnv.setAttackTime(decay * 2.f);
    spikeRemoverEnv.setReleaseTime(decay);

    outGain = juce::Decibels::decibelsToGain(gain);
}

void UpDownComp::updateTimes(const float attack, const float decay)
{
    envelope.setAttackTime(attack * 0.5f);
    envelope.setReleaseTime(decay);

    spikeRemoverEnv.setAttackTime(decay * 2.f);
    spikeRemoverEnv.setReleaseTime(decay);
}

float UpDownComp::processSample(int channel, float sample)
{
    const auto env = envelope.processSample(channel, sample);

    // Helps midigate awful transients when going from silence, to sound
    //   What if the ableton compressor makes the 'attack' really short when
    //   going from silence to sound??
    auto spikeRemover = spikeRemoverEnv.processSample(
        channel, float(sample > loudnessCutoff));
    spikeRemover = juce::jmap(std::min(spikeRemover, 0.5f), 0.f, 0.5f, 0.f, 1.f);

    float gain = 1.f;
    if (env > paramsDown.thresh) // downward compression
        gain = std::pow(env * paramsDown.invThresh, paramsDown.invRatio - 1.f);
    else if (env < paramsUp.thresh && env > loudnessCutoff) // upwards
    {
        gain = std::pow(env * paramsUp.invThresh, paramsUp.invRatio - 1.f);
        gain = juce::jmap(spikeRemover, 1.f, gain);
    }

    return sample * gain * outGain;
}
}