/*
  ==============================================================================

    FonzLayout.h
    Created: 5 Sep 2022 5:44:16pm
    Author:  thesp

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../Utils/GuiData.h"
#include "../Utils/FullSlider.h"

class FonzLayout  : public juce::Component
{
public:
    FonzLayout(xynth::GuiData&);
    ~FonzLayout() = default;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    xynth::GuiData& guiData;
    xynth::FullSlider slider;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FonzLayout)
};
