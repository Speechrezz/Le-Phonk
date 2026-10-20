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

DistGraph::DistGraph(xynth::GuiData& g) : guiData(g)
{
    startTimerHz(60);
    gainAtomic   = g.audioProcessor.treeState.getRawParameterValue(ZEKETE_ID);
    selectAtomic = g.audioProcessor.treeState.getRawParameterValue(DIST_SELECT_ID);
}

void DistGraph::paint (juce::Graphics& g)
{
    auto& lnf = guiData.getLnf();
    auto rect = getLocalBounds().toFloat();

    juce::Path clip;
    clip.addRoundedRectangle(rect, 8.f);
    g.reduceClipRegion(clip);

    // Load parameters and audio
    const int idx = int(selectAtomic->load(std::memory_order_relaxed));
    const float param = gainAtomic->load(std::memory_order_relaxed) * 0.01f;

    lnf.drawDistGraphBackground(g, rect, std::tanh(sample * juce::mapToLog10(param, 1.f, 12.f) * 0.2f));

    // Maximum points on x-axis
    const float maxGain = xynth::xAxisFromAmount(idx, param);
    const float stepSize = maxGain / 200.f / (1.f + param * 3.f);

    // Draw background path
    juce::Path p;
    p.startNewSubPath(-maxGain, -1.f);
    p.startNewSubPath( maxGain,  1.f);
    p.startNewSubPath(-maxGain, -xynth::distortSampleVisualization(idx, -maxGain, param));
    for (float pos = -maxGain; pos <= maxGain; pos += stepSize)
        p.lineTo(pos, -xynth::distortSampleVisualization(idx, pos, param));

    const auto transform = p.getTransformToScaleToFit(rect.reduced(0.f, 12.f), false, juce::Justification::centred);
    g.setColour(lnf.getNeutral1());
    g.strokePath(p, juce::PathStrokeType(3.f), transform);

    // Draw foreground path
    juce::Path fg;
    fg.startNewSubPath(-sample, -xynth::distortSampleVisualization(idx, -sample, param));
    for (float pos = -sample; pos <= sample; pos += stepSize)
        fg.lineTo(pos, -xynth::distortSampleVisualization(idx, pos, param));

    // Have the fg path fade out
    const float alpha = std::min(1.f, sample * 50.f / maxGain);
    g.setColour(lnf.getAccent2().withAlpha(alpha));
    g.strokePath(fg, juce::PathStrokeType(4.f, juce::PathStrokeType::mitered, juce::PathStrokeType::rounded), transform);

    lnf.drawDistGraphForeground(g, rect);
}

void DistGraph::timerCallback()
{
    constexpr float decayFactor = 0.92f;

    const auto newSample = guiData.audioProcessor.ringBuffer.readLoudestSample();
    if (newSample >= 0.f)
    {
        const float decayedSample = sample * decayFactor;
        sample = newSample > decayedSample ? newSample : decayedSample;
        repaint();
    }
}
