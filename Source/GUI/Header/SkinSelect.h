/*
  ==============================================================================

    SkinSelect.h
    Created: 7 Sep 2022 3:08:25pm
    Author:  thesp

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../Utils/GuiData.h"

class SkinSelect  : public juce::Component
{
public:
    SkinSelect(xynth::GuiData&);
    ~SkinSelect() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void mouseEnter(const juce::MouseEvent& e) override;
    void mouseExit (const juce::MouseEvent& e) override;

private:
    void updateSkin();

    xynth::GuiData& guiData;
    juce::StringArray skinNames{ "Hell", "Juice", "Drippy" };
    juce::ComboBox dropDown;

    juce::NotificationType notif{ juce::NotificationType::dontSendNotification };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SkinSelect)
};
