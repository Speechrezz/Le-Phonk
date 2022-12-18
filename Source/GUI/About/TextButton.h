/*
  ==============================================================================

    TextButton.h
    Created: 18 Dec 2022 6:12:03pm
    Author:  thesp

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../Utils/GuiData.h"

namespace xynth
{
class TextButton : public juce::TextButton
{
public:
    TextButton(xynth::GuiData&);

    void paint(juce::Graphics&) override;

    void mouseEnter(const juce::MouseEvent& e) override;
    void mouseExit(const juce::MouseEvent& e) override;

    void setFillIn(const bool shouldFillIn);
    void setText(const juce::String newText);

private:
    xynth::GuiData& guiData;

    bool fillInButton = true;
    juce::String buttonText;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TextButton)
};
} // namespace xynth