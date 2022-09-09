/*
  ==============================================================================

    LogoButton.h
    Created: 8 Sep 2022 4:59:35pm
    Author:  thesp

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../Utils/GuiData.h"

class LogoButton  : public juce::Component
{
public:
    LogoButton(xynth::GuiData&);
    ~LogoButton() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void mouseDown(const juce::MouseEvent& e) override;

private:
    xynth::GuiData& guiData;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LogoButton)
};
