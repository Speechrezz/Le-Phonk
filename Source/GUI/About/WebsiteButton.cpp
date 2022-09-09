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
    onClick = []() { juce::URL("http://xynthaudio.com/").launchInDefaultBrowser(); };
}

WebsiteButton::~WebsiteButton()
{
}

void WebsiteButton::paint (juce::Graphics& g)
{
    auto rect = getLocalBounds().toFloat();
    auto& lnf = guiData.getLnf();

    auto bgCol = lnf.getAccent2().brighter(isMouseOver() ? 0.15f : 0.f);
    bgCol = bgCol.darker(isMouseButtonDown() ? 0.2f : 0.f);
    g.setColour(bgCol);
    g.fillRoundedRectangle(rect, 6.f);

    g.setColour(lnf.getBase1());
    g.setFont(lnf.getCustomFontMedium().withHeight(32.f));
    g.drawText("Visit Website", rect, juce::Justification::centred);
}

void WebsiteButton::resized()
{
}
