/*
  ==============================================================================

    OttzLayout.cpp
    Created: 5 Sep 2022 5:44:06pm
    Author:  thesp

  ==============================================================================
*/

#include <JuceHeader.h>
#include "OttzLayout.h"

OttzLayout::OttzLayout(xynth::GuiData& g) : guiData(g), timeKnob(g), toggleButton(g, OTT_ENABLE_ID)
{
    auto& treeState = g.audioProcessor.treeState;

    slider.init(treeState, OTT_ID);
    slider.slider.setDescription(OTT_NAME);
    addAndMakeVisible(slider.slider);
    addAndMakeVisible(timeKnob);
    addAndMakeVisible(toggleButton);
}

void OttzLayout::paint (juce::Graphics& g)
{
    slider.slider.setColour(juce::Slider::rotarySliderFillColourId,    guiData.getLnf().getNeutral1());
    slider.slider.setColour(juce::Slider::rotarySliderOutlineColourId, guiData.getLnf().getAccent1());

    toggleButton.setColour(juce::ToggleButton::ColourIds::tickColourId, guiData.getLnf().getAccent1());
    toggleButton.setColour(juce::ToggleButton::ColourIds::tickDisabledColourId, guiData.getLnf().getAccent1().withAlpha(0.4f));

    const float alpha = toggleButton.getToggleState() ? 1.f : 0.4f;
    slider.slider.setAlpha(alpha);
    timeKnob.setAlpha(alpha);

    auto rect = getLocalBounds();
    auto textRect = rect.removeFromTop(41);
    guiData.getLnf().drawSectionBackground(g, rect);

    g.setColour(guiData.getLnf().getAccent1());
    g.setFont(guiData.getLnf().getCustomFontSemiBold());
    g.drawText("Le Ottz", textRect, juce::Justification::centredTop);
}

void OttzLayout::resized()
{
    auto rect = getLocalBounds();
    rect.removeFromTop(41);
    slider.slider.setBounds(rect.withSizeKeepingCentre(74, 74));
    rect.removeFromRight(2 * rect.getWidth() / 3 - 10);
    timeKnob.setBounds(rect.withSizeKeepingCentre(64, 74));

    juce::Rectangle<int> toggleRect(0, 0, 20, 44);
    toggleButton.setBounds(toggleRect.reduced(0, 9));

}
