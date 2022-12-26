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
    void resized() override;

    void showTooltip(juce::Point<int> screenPosition, const juce::String& prefixText);
    void updateTooltipValue(const juce::String& newValue);
    void hideTooltip();

private:
    xynth::GuiData& guiData;

    juce::String prefixText, valueText;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TooltipLabel)
};
} // namespace xynth