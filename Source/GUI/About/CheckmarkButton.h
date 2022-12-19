/*
  ==============================================================================

    CheckmarkButton.h
    Created: 18 Dec 2022 6:12:03pm
    Author:  thesp

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../Utils/GuiData.h"

namespace xynth
{
class CheckmarkButton : public juce::TextButton
{
public:
    CheckmarkButton(xynth::GuiData&);

    void paint(juce::Graphics&) override;

    void mouseEnter(const juce::MouseEvent& e) override;
    void mouseExit(const juce::MouseEvent& e) override;

    void setText(const juce::String newText);

private:
    xynth::GuiData& guiData;

    juce::String buttonText;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CheckmarkButton)
};
} // namespace xynth