/*
  ==============================================================================

    GuiData.h
    Created: 5 Sep 2022 3:56:01pm
    Author:  thesp

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "../../PluginProcessor.h"
#include "../CustomLooks/CustomLook.h"

namespace xynth
{
struct GuiData
{
    GuiData(LePhonkAudioProcessor& p, juce::CustomLook& lnf, double& s)
        : audioProcessor(p), scale(s), customLook(lnf) {}

    LePhonkAudioProcessor& audioProcessor;
    juce::CustomLook& customLook;
    double& scale;
};
} //namespace xynth