/*
  ==============================================================================

    TooltipLabel.h
    Created: 25 Dec 2022 2:03:01pm
    Author:  thesp

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "GuiData.h"

namespace xynth
{
class TooltipLabel : public juce::Component
{
public:
    TooltipLabel(xynth::GuiData&);
    ~TooltipLabel() = default;

    void paint(juce::Graphics&) override;

    void showTooltip(juce::Point<int> screenPosition);
    void updateTooltipText(const juce::String& newText);
    void hideTooltip();

private:
    xynth::GuiData& guiData;

    juce::String tooltipText;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TooltipLabel)
};
} // namespace xynth