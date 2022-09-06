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

namespace xynth
{
struct GuiData
{
    GuiData(LePhonkAudioProcessor& p, double& s) : audioProcessor(p), scale(s) {}

    LePhonkAudioProcessor& audioProcessor;
    double& scale;
};
} //namespace xynth