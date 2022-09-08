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

class DistSelect  : public juce::Component
{
public:
    DistSelect(xynth::GuiData&);
    ~DistSelect() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void mouseEnter(const juce::MouseEvent& e) override;
    void mouseExit (const juce::MouseEvent& e) override;

private:
    using cbAttach = juce::AudioProcessorValueTreeState::ComboBoxAttachment;

    xynth::GuiData& guiData;

    juce::StringArray distNames{ "Hell", "Juice", "Drippy" };
    juce::ComboBox dropDown;
    std::unique_ptr<cbAttach> dropDownAttach;

    juce::NotificationType notif{ juce::NotificationType::dontSendNotification };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DistSelect)
};
