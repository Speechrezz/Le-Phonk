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
#include "Utils/TooltipLabel.h"
#include "Zekete/ZeketeLayout.h"
#include "Ottz/OttzLayout.h"
#include "Fonz/FonzLayout.h"
#include "Header/BypassGain.h"
#include "Header/SkinSelect.h"
#include "Header/LogoButton.h"
#include "About/AboutOverlay.h"

class WindowLayout : public juce::Component
{
public:
    WindowLayout(xynth::GuiData&);
    ~WindowLayout() = default;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    xynth::GuiData& guiData;
    xynth::TooltipLabel tooltip;
    ZeketeLayout zeketeLayout;
    OttzLayout   ottzLayout;
    FonzLayout   fonzLayout;
    BypassGain   bypassGain;
    SkinSelect   skinSelect;
    LogoButton   logoButton;
    AboutOverlay aboutOverlay;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WindowLayout)
};
