/*
  ==============================================================================

    DistGraph.cpp
    Created: 6 Sep 2022 12:07:31pm
    Author:  thesp

  ==============================================================================
*/

#include <JuceHeader.h>
#include "DistGraph.h"

//==============================================================================
DistGraph::DistGraph(xynth::GuiData& g) : guiData(g)
{

}

DistGraph::~DistGraph()
{
}

void DistGraph::paint (juce::Graphics& g)
{
    auto& look = guiData.customLook;
    auto rect = getLocalBounds();

    look.drawDistGraphBackground(g, rect.toFloat());
    look.drawDistGraphForeground(g, rect.toFloat());
}

void DistGraph::resized()
{

}
