/*
  ==============================================================================

    WindowLayout.h
    Created: 5 Sep 2022 3:26:44pm
    Author:  thesp

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../Common/Constants.h"
#include "Utils/FullSlider.h"
#include "Utils/GuiData.h"

//==============================================================================
/*
*/
class WindowLayout : public juce::Component
{
public:
    WindowLayout(xynth::GuiData&);
    ~WindowLayout() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    xynth::GuiData& guiData;
    xynth::FullSlider OTT, Lemonz, Zekete;

    juce::Image backgroundImage;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WindowLayout)
};
