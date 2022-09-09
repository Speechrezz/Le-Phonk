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
    ~WebsiteButton() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    xynth::GuiData& guiData;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WebsiteButton)
};
