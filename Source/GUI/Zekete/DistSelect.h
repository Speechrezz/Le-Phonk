/*
  ==============================================================================

    DistSelect.h
    Created: 8 Sep 2022 4:01:58pm
    Author:  thesp

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../Utils/GuiData.h"

class DistSelect  : public juce::ComboBox
{
public:
    DistSelect(xynth::GuiData&);

    void mouseEnter(const juce::MouseEvent& e) override;
    void mouseExit (const juce::MouseEvent& e) override;

    void mouseWheelMove(const juce::MouseEvent& e, const juce::MouseWheelDetails& mw) override;

private:
    xynth::GuiData& guiData;

    using cbAttach = juce::AudioProcessorValueTreeState::ComboBoxAttachment;
    std::unique_ptr<cbAttach> dropDownAttach;

    float mwMovement{ 0.f };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DistSelect)
};
