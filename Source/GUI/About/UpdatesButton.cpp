/*
  ==============================================================================

    UpdatesButton.cpp
    Created: 8 Sep 2022 6:12:03pm
    Author:  thesp

  ==============================================================================
*/

#include <JuceHeader.h>
#include "UpdatesButton.h"

UpdatesButton::UpdatesButton(xynth::GuiData& g) : guiData(g)
{}

void UpdatesButton::paint (juce::Graphics& g)
{
    auto rect = getLocalBounds().toFloat();
    auto& lnf = guiData.getLnf();

    auto bgCol = lnf.getAccent2().brighter(isMouseOver() ? 0.15f : 0.f);
    bgCol = bgCol.darker(isMouseButtonDown() ? 0.2f : 0.f);
    g.setColour(bgCol);
    g.fillRoundedRectangle(rect, 6.f);

    g.setColour(lnf.getBase1());
    g.setFont(lnf.getCustomFontMedium().withHeight(24.f));
    g.drawText("Check Updates", rect, juce::Justification::centred);
}

void UpdatesButton::mouseEnter(const juce::MouseEvent& e)
{
    setMouseCursor(juce::MouseCursor::PointingHandCursor);
    juce::TextButton::mouseEnter(e);
}

void UpdatesButton::mouseExit(const juce::MouseEvent& e)
{
    setMouseCursor(juce::MouseCursor::NormalCursor);
    juce::TextButton::mouseExit(e);
}
