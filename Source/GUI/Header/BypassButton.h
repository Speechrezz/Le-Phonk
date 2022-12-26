/*
  ==============================================================================

    BypassButton.h
    Created: 7 Sep 2022 11:04:29am
    Author:  thesp

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../Utils/GuiData.h"
#include "../Utils/FullSlider.h"

namespace xynth
{
class BypassButton : public juce::ToggleButton
{
public:
    BypassButton(xynth::GuiData&, juce::String);
    ~BypassButton() = default;

private:
    xynth::GuiData& guiData;
    juce::AudioProcessorValueTreeState::ButtonAttachment attach;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(BypassButton)
};
} // namespace xynth