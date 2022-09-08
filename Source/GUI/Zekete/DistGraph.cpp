/*
  ==============================================================================

    DistGraph.cpp
    Created: 6 Sep 2022 12:07:31pm
    Author:  thesp

  ==============================================================================
*/

#include <JuceHeader.h>
#include "DistGraph.h"
#include "../../Common/Constants.h"

//==============================================================================
DistGraph::DistGraph(xynth::GuiData& g) : guiData(g)
{
    startTimerHz(60);
    gainAtomic = g.audioProcessor.treeState.getRawParameterValue(ZEKETE_ID);
    
}

DistGraph::~DistGraph()
{
}

void DistGraph::paint (juce::Graphics& g)
{
    auto& look = guiData.getLnf();
    auto rect = getLocalBounds().toFloat();

    juce::Path clip;
    clip.addRoundedRectangle(rect, 8.f);
    g.reduceClipRegion(clip);

    const float dB = juce::jmap(gainAtomic->load(std::memory_order_relaxed) * 0.01f, 0.f, ZEKETE_MAX_DB);
    const float gain = juce::Decibels::decibelsToGain(dB);
    const float newSample = guiData.audioProcessor.ringBuffer.readSamples() * gain;

    const float maxGain = std::sqrt(gain);
    const float stepSize = maxGain / 200.f;

    sample = newSample > sample ? newSample : sample * 0.92f;
    
    look.drawDistGraphBackground(g, rect, std::tanh(sample * 0.2f));

    juce::Path p;
    p.startNewSubPath(-maxGain, -std::tanh(-maxGain));
    for (float pos = -maxGain; pos <= maxGain; pos += stepSize)
        p.lineTo(pos, -std::tanh(pos));

    const auto transform = p.getTransformToScaleToFit(rect.reduced(0.f, 12.f), false, juce::Justification::centred);
    g.setColour(look.getNeutral1());
    g.strokePath(p, juce::PathStrokeType(3.f), transform);

    juce::Path fg;
    fg.startNewSubPath(-sample, -std::tanh(-sample));
    for (float pos = -sample; pos <= sample; pos += stepSize)
        fg.lineTo(pos, -std::tanh(pos));

    const float alpha = std::min(1.f, sample * 40.f);
    g.setColour(look.getAccent2().withAlpha(alpha));
    g.strokePath(fg, juce::PathStrokeType(4.f, juce::PathStrokeType::mitered, juce::PathStrokeType::rounded), transform);

    look.drawDistGraphForeground(g, rect);
}

void DistGraph::resized()
{

}

void DistGraph::timerCallback()
{
    repaint();
}
