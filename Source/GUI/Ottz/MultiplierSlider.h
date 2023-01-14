/*
  ==============================================================================

    MultiplierSlider.h
    Created: 13 Jan 2023 5:36:32pm
    Author:  thesp

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../Utils/GuiData.h"

namespace xynth
{
class MultiplierSlider : public juce::Slider
{
public:
    MultiplierSlider(xynth::GuiData&);

    void paint(juce::Graphics&) override;
    void resized() override;

    void mouseEnter(const juce::MouseEvent& e) override;
    void mouseExit (const juce::MouseEvent& e) override;

private:
    xynth::GuiData& guiData;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> attach;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MultiplierSlider)
};
} // namespace xynth