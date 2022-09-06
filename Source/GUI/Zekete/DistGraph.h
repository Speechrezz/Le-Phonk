/*
  ==============================================================================

    DistGraph.h
    Created: 6 Sep 2022 12:07:31pm
    Author:  thesp

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../Utils/GuiData.h"

class DistGraph  : public juce::Component
{
public:
    DistGraph(xynth::GuiData&);
    ~DistGraph() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    xynth::GuiData& guiData;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DistGraph)
};
