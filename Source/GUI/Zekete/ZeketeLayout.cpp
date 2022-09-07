/*
  ==============================================================================

    ZeketeLayout.cpp
    Created: 5 Sep 2022 5:20:41pm
    Author:  thesp

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ZeketeLayout.h"

ZeketeLayout::ZeketeLayout(xynth::GuiData& g) : guiData(g), distGraph(g)
{
    auto& treeState = g.audioProcessor.treeState;

    slider.init(treeState, ZEKETE_ID);
    slider.slider.setSliderStyle(juce::Slider::LinearHorizontal);
    slider.slider.setSliderSnapsToMousePosition(false);
    addAndMakeVisible(slider.slider);
    addAndMakeVisible(distGraph);
}

ZeketeLayout::~ZeketeLayout()
{
}

void ZeketeLayout::paint (juce::Graphics& g)
{
    auto& look = guiData.customLook;
    auto rect = getLocalBounds();
    look.drawSectionBackground(g, rect);

    g.setColour(look.getAccent1());
    g.setFont(look.getCustomFontSemiBold());
    g.drawText("Zekete", rect.removeFromTop(44), juce::Justification::centred);
    g.drawLine(29.f, 46.f, float(getWidth()) - 29.f, 46.f, 2.f);
}

void ZeketeLayout::resized()
{
    auto rect = getLocalBounds();
    distGraph.setBounds(rect.removeFromBottom(177));
    slider.slider.setBounds(rect.withSizeKeepingCentre(246, 74));
}
