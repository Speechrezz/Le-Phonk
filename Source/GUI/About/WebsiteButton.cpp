/*
  ==============================================================================

    WebsiteButton.cpp
    Created: 8 Sep 2022 6:12:03pm
    Author:  thesp

  ==============================================================================
*/

#include <JuceHeader.h>
#include "WebsiteButton.h"

WebsiteButton::WebsiteButton(xynth::GuiData& g) : guiData(g)
{
    onClick = []() { juce::URL("https://www.xynthaudio.com/plugins/lephonk").launchInDefaultBrowser(); };
}


void WebsiteButton::paint (juce::Graphics& g)
{
    auto rect = getLocalBounds().toFloat();
    auto& lnf = guiData.getLnf();
    const float thickness = 1.5f;

    auto mainCol = lnf.getAccent2().brighter(isMouseOver() ? 0.15f : 0.f);
    mainCol = mainCol.darker(isMouseButtonDown() ? 0.2f : 0.f);
    g.setColour(mainCol);
    g.drawRoundedRectangle(rect.reduced(thickness / 2.f), 6.f, thickness);

    g.setFont(lnf.getCustomFontMedium().withHeight(24.f));
    g.drawText("Visit Website", rect, juce::Justification::centred);
}

void WebsiteButton::mouseEnter(const juce::MouseEvent& e)
{
    setMouseCursor(juce::MouseCursor::PointingHandCursor);
    juce::TextButton::mouseEnter(e);
}

void WebsiteButton::mouseExit(const juce::MouseEvent& e)
{
    setMouseCursor(juce::MouseCursor::NormalCursor);
    juce::TextButton::mouseExit(e);
}
