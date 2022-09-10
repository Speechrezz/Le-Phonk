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
void Dist3::prepare(const juce::dsp::ProcessSpec& spec)
{
    float cutoff = 200.f;
    const float cutoffStep = 3.f;
    for (auto& filter : allPassFilters)
    {
        filter.prepare(spec);
        //*filter.state = *juce::dsp::IIR::Coefficients<float>::makeAllPass(spec.sampleRate, cutoff);
        filter.updateParameters(cutoff);
        cutoff += cutoffStep;
    }

    gainOut.prepare(spec);
    gainOut.setRampDurationSeconds(0.01);
    gainOut.setGainLinear(1.f);

    inter.prepare(spec);
}

void Dist3::process(juce::dsp::ProcessContextReplacing<float>& context)
{
    float param = paramAtomic->load(std::memory_order_relaxed) * 0.01f;
    param = range.convertFrom0to1(param);
    const int idx = int(juce::jmap(param, 1.f, float(allPassFilters.size())));
    
    // Gain smoothing when moving slider to mitigate popping sounds
    gainOut.setGainLinear(float(idx == prevIdx));

    processAllPass(context, prevIdx);
    gainOut.process(context);

    if (!gainOut.isSmoothing())
        prevIdx = idx;
}

void Dist3::setAtomics(juce::AudioProcessorValueTreeState& treeState)
{
    paramAtomic = treeState.getRawParameterValue(ZEKETE_ID);
}
void Dist3::processAllPass(juce::dsp::ProcessContextReplacing<float>& context, int idx)
{
    jassert(idx >= 0 && idx <= allPassFilters.size());

    inter.interleave(context);

    for (int i = 0; i < idx; ++i)
        allPassFilters[i].process(inter.getInterleavedAudio());

    inter.deinterleave(context);

    /*for (int i = idx; i < allPassFilters.size(); ++i)
        allPassFilters[i].reset();*/
}
} // namespace xynth