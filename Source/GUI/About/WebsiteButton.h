/*
  ==============================================================================

    WebsiteButton.h
    Created: 8 Sep 2022 6:12:03pm
    Author:  thesp

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../Utils/GuiData.h"

class WebsiteButton  : public juce::TextButton
{
public:
    WebsiteButton(xynth::GuiData&);

    void paint (juce::Graphics&) override;

    void mouseEnter(const juce::MouseEvent& e) override;
    void mouseExit (const juce::MouseEvent& e) override;

private:
    xynth::GuiData& guiData;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WebsiteButton)
};
