/*
  ==============================================================================

    BackButton.h
    Created: 11 Nov 2022 6:12:03pm
    Author:  thesp

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../../Utils/GuiData.h"

namespace xynth 
{
class BackButton : public juce::TextButton
{
public:
    BackButton(xynth::GuiData&);

    void paint(juce::Graphics&) override;

    void mouseEnter(const juce::MouseEvent& e) override;
    void mouseExit(const juce::MouseEvent& e) override;

private:
    xynth::GuiData& guiData;
    std::unique_ptr<juce::Drawable> backArrow;

    juce::Colour previousColour = juce::Colours::white;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(BackButton)
};
} // namespace xynth