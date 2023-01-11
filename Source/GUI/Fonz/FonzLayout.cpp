/*
  ==============================================================================

    FonzLayout.cpp
    Created: 5 Sep 2022 5:44:16pm
    Author:  thesp

  ==============================================================================
*/

#include <JuceHeader.h>
#include "FonzLayout.h"

FonzLayout::FonzLayout(xynth::GuiData& g) : guiData(g), toggleButton(g, FONZ_ENABLE_ID)
{
    auto& treeState = g.audioProcessor.treeState;

    slider.init(treeState, FONZ_ID);
    slider.slider.setDescription(FONZ_NAME);
    addAndMakeVisible(slider.slider);
    addAndMakeVisible(toggleButton);
}

void FonzLayout::paint (juce::Graphics& g)
{
    slider.slider.setColour(juce::Slider::rotarySliderFillColourId,    guiData.getLnf().getNeutral1());
    slider.slider.setColour(juce::Slider::rotarySliderOutlineColourId, guiData.getLnf().getAccent1());

    toggleButton.setColour(juce::ToggleButton::ColourIds::tickColourId, guiData.getLnf().getAccent1());
    toggleButton.setColour(juce::ToggleButton::ColourIds::tickDisabledColourId, guiData.getLnf().getAccent1().withAlpha(0.4f));

    const float alpha = toggleButton.getToggleState() ? 1.f : 0.4f;
    slider.slider.setAlpha(alpha);

    auto rect = getLocalBounds();
    auto textRect = rect.removeFromTop(41);
    guiData.getLnf().drawSectionBackground(g, rect);

    g.setColour(guiData.getLnf().getAccent1());
    g.setFont(guiData.getLnf().getCustomFontSemiBold());
    g.drawText("Le Fonz", textRect, juce::Justification::centredTop);
}

void FonzLayout::resized()
{
    auto rect = getLocalBounds();
    rect.removeFromTop(41);
    rect = rect.withSizeKeepingCentre(74, 74);
    slider.slider.setBounds(rect);

    juce::Rectangle<int> toggleRect(0, 0, 20, 44);
    toggleButton.setBounds(toggleRect.reduced(0, 9));
}
