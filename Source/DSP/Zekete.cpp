/*
  ==============================================================================

    Zekete.cpp
    Created: 3 Sep 2022 11:27:40am
    Author:  thesp

  ==============================================================================
*/

#include "Zekete.h"
#include "../Common/Constants.h"

namespace xynth
{
Zekete::Zekete()
{
    shaper.functionToUse = [](float x)
    {
        return std::tanh(x);
    };
}
void Zekete::prepare(const juce::dsp::ProcessSpec& spec)
{
    gainIn.prepare(spec);
    gainIn.setRampDurationSeconds(0.005);

    gainOut.prepare(spec);
    gainOut.setRampDurationSeconds(0.005);

    shaper.prepare(spec);

    for (auto& filter : filters)
        filter.prepare(spec);

    *filters[before].state = *juce::dsp::IIR::Coefficients<float>::makePeakFilter(spec.sampleRate, 555.f, 1.2f, 4.f);
    *filters[after].state  = *juce::dsp::IIR::Coefficients<float>::makePeakFilter(spec.sampleRate, 555.f, 1.2f, 1.f / 4.f);
}
void Zekete::process(juce::dsp::ProcessContextReplacing<float>& context)
{
    float dB = paramAtomic->load(std::memory_order_relaxed) * 0.01f;
    dB = juce::jmap(dB, 0.f, 24.f);
    gainIn.setGainDecibels(dB);
    gainOut.setGainDecibels(dB * -0.9f);

    filters[before].process(context);
    gainIn.process (context);
    shaper.process (context);
    gainOut.process(context);
    filters[after].process(context);
}
void Zekete::setAtomics(juce::AudioProcessorValueTreeState& treeState)
{
    paramAtomic = treeState.getRawParameterValue(ZEKETE_ID);
}
} // namespace xynth