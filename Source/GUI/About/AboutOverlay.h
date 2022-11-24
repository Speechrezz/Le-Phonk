/*
  ==============================================================================

    AboutOverlay.h
    Created: 8 Sep 2022 5:08:12pm
    Author:  thesp

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "AboutWindow.h"
#include "../Utils/GuiData.h"
#include "UpdateCheck/ServerCheck.h"

class AboutOverlay  : public juce::Component
{
public:
    AboutOverlay(xynth::GuiData&);
    ~AboutOverlay() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    void mouseDown(const juce::MouseEvent& e) override;

    // Called when about menu is just opened
    void opened();

private:
    xynth::GuiData& guiData;
    AboutWindow aboutWindow;
    
    xynth::ServerCheck serverCheck;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AboutOverlay)
};
