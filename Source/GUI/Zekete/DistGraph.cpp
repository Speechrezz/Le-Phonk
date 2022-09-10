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
    gainAtomic   = g.audioProcessor.treeState.getRawParameterValue(ZEKETE_ID);
    selectAtomic = g.audioProcessor.treeState.getRawParameterValue(DIST_SELECT_ID);
}

DistGraph::~DistGraph()
{
}

void DistGraph::paint (juce::Graphics& g)
{
    auto& look = guiData.getLnf();
    auto& ap = guiData.audioProcessor;
    auto rect = getLocalBounds().toFloat();

    juce::Path clip;
    clip.addRoundedRectangle(rect, 8.f);
    g.reduceClipRegion(clip);
    look.drawDistGraphBackground(g, rect, std::tanh(sample * 0.2f));

    // Load parameters and audio
    const int idx = int(selectAtomic->load(std::memory_order_relaxed));
    const float dB = juce::jmap(gainAtomic->load(std::memory_order_relaxed) * 0.01f, 0.f, ZEKETE_MAX_DB);
    const float gain = juce::Decibels::decibelsToGain(dB);
    const float newSample = guiData.audioProcessor.ringBuffer.readSamples() * gain;
    sample = newSample > sample ? newSample : sample * 0.92f;

    // Maximum points on x-axis
    const float maxGain = 1;
    const float stepSize = maxGain / 200.f;

    // Draw background path
    juce::Path p;
    p.startNewSubPath(-maxGain, -1.f);
    p.startNewSubPath(maxGain, 1.f);
    p.startNewSubPath(-maxGain, -ap.zeketeDistort(-maxGain, idx));
    for (float pos = -maxGain; pos <= maxGain; pos += stepSize)
        p.lineTo(pos, -ap.zeketeDistort(pos, idx));

    const auto transform = p.getTransformToScaleToFit(rect.reduced(0.f, 12.f), false, juce::Justification::centred);
    g.setColour(look.getNeutral1());
    g.strokePath(p, juce::PathStrokeType(3.f), transform);

    // Draw foreground path
    juce::Path fg;
    fg.startNewSubPath(-sample, -ap.zeketeDistort(-sample, idx));
    for (float pos = -sample; pos <= sample; pos += stepSize)
        fg.lineTo(pos, -ap.zeketeDistort(pos, idx));

    // Have the fg path fade out
    const float alpha = std::min(1.f, sample * 40.f / maxGain);
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
