/*
  ==============================================================================

    TooltipSlider.h
    Created: 25 Dec 2022 6:55:51pm
    Author:  thesp

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "GuiData.h"

namespace xynth
{
class TooltipSlider : public juce::Slider
{
public:
    TooltipSlider(xynth::GuiData&);
    ~TooltipSlider() = default;

    void mouseEnter(const juce::MouseEvent& e) override;
    void mouseExit (const juce::MouseEvent& e) override;

    void assignParameter(const juce::String& paramID);
    void setName(const juce::String& newName) override { name = newName; }
    void setPostfix(const juce::String& newPostfix) { postfix = newPostfix; }
    void valueChanged() override;

    void resized() override;

private:
    xynth::GuiData& guiData;
    juce::String name, postfix;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> attach;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TooltipSlider)
};
} // namespace xynth