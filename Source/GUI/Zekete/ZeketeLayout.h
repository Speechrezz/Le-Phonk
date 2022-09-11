/*
  ==============================================================================

    ZeketeLayout.h
    Created: 5 Sep 2022 5:20:41pm
    Author:  thesp

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../Utils/GuiData.h"
#include "../Utils/FullSlider.h"
#include "DistGraph.h"
#include "DistSelect.h"

class ZeketeLayout  : public juce::Component
{
public:
    ZeketeLayout(xynth::GuiData&);
    ~ZeketeLayout() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    xynth::GuiData& guiData;
    xynth::FullSlider slider;
    xynth::FullSlider mix;
    DistGraph distGraph;
    DistSelect distSelect;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ZeketeLayout)
};
