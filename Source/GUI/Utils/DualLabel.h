/*
  ==============================================================================

    DualLabel.h
    Created: 25 Dec 2022 10:13:24am
    Author:  thesp

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

namespace xynth
{
class DualLabel : public juce::Label
{
public:
    DualLabel(juce::Slider&);
    ~DualLabel() = default;

    void paint(juce::Graphics&) override;

    void mouseEnter(const juce::MouseEvent& e) override;
    void mouseExit (const juce::MouseEvent& e) override;

private:
    juce::Slider& parentSlider;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DualLabel)
};
}