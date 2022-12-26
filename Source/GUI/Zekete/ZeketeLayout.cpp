/*
  ==============================================================================

    ZeketeLayout.cpp
    Created: 5 Sep 2022 5:20:41pm
    Author:  thesp

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ZeketeLayout.h"

ZeketeLayout::ZeketeLayout(xynth::GuiData& g) : guiData(g), distGraph(g), distSelect(g), mixSlider(g)
{
    auto& treeState = g.audioProcessor.treeState;

    slider.init(treeState, ZEKETE_ID);
    slider.slider.setSliderStyle(juce::Slider::LinearHorizontal);
    slider.slider.setSliderSnapsToMousePosition(false);

    mixSlider.assignParameter(ZEKETE_MIX_ID);
    mixSlider.setName("Mix");
    mixSlider.setPostfix("%");

    addAndMakeVisible(slider.slider);
    addAndMakeVisible(mixSlider);
    addAndMakeVisible(distGraph);
    addAndMakeVisible(distSelect);
}

void ZeketeLayout::paint (juce::Graphics& g)
{
    mixSlider.setColour(juce::Slider::rotarySliderFillColourId, guiData.getLnf().getNeutral1());
    mixSlider.setColour(juce::Slider::rotarySliderOutlineColourId, guiData.getLnf().getAccent2());

    auto& look = guiData.getLnf();
    auto rect = getLocalBounds();
    look.drawSectionBackground(g, rect);

    g.setColour(look.getAccent2());
    g.setFont(look.getCustomFontSemiBold());
    g.drawText("Zekete", rect.removeFromTop(44), juce::Justification::centred);
    g.drawLine(29.f, 46.f, float(getWidth()) - 29.f, 46.f, 2.f);
}

void ZeketeLayout::resized()
{
    auto rect = getLocalBounds();
    distGraph.setBounds(rect.removeFromBottom(177));
    rect.removeFromBottom(30);
    slider.slider.setBounds(rect.removeFromBottom(16).reduced(23, 0));
    rect.removeFromBottom(26);
    distSelect.setBounds(rect.removeFromBottom(32).reduced(29, 0));

    rect.removeFromTop(11);
    rect.removeFromLeft(26);
    mixSlider.setBounds(rect.removeFromTop(25).withWidth(25));
}
