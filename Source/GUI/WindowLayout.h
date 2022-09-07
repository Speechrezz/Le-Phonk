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
#include "Zekete/ZeketeLayout.h"
#include "Ottz/OttzLayout.h"
#include "Fonz/FonzLayout.h"
#include "Header/BypassGain.h"

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
    ZeketeLayout zeketeLayout;
    OttzLayout   ottzLayout;
    FonzLayout   fonzLayout;
    BypassGain   bypassGain;

    juce::Image backgroundImage;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WindowLayout)
};
