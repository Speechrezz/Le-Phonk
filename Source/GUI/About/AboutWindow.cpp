/*
  ==============================================================================

    AboutWindow.cpp
    Created: 8 Sep 2022 5:08:23pm
    Author:  thesp

  ==============================================================================
*/

#include <JuceHeader.h>
#include "AboutWindow.h"

AboutWindow::AboutWindow(xynth::GuiData& g) : guiData(g)
{
}

AboutWindow::~AboutWindow()
{
}

void AboutWindow::paint (juce::Graphics& g)
{
    auto rect = getLocalBounds().toFloat();
    auto& lnf = guiData.getLnf();

    g.setColour(lnf.getBase1().darker());
    g.fillRoundedRectangle(rect, 8.f);
    g.setColour(lnf.getNeutral1());
    g.drawRoundedRectangle(rect.reduced(1.f), 8.f, 2.f);

    g.setColour (lnf.getAccent2());
    g.setFont(lnf.getCustomFontSemiBold());
    g.drawText("About us", rect.removeFromTop(60.f), juce::Justification::centred);

    rect.removeFromTop(48.f);
    auto textRect = rect.reduced(20.f, 0.f);
    g.setColour(lnf.getNeutral1().brighter(1.f));
    g.setFont(lnf.getCustomFontMedium().withHeight(22.f));
    g.drawMultiLineText("Skybreak was born on Janurary 17th, 2019 and died on saturday. "
        "Did you know: he originally developed the first lephonk plugin? from paper "
        "skys brain, skybreak made a version then sharks made a version the speechrezz "
        "made the best version and sharks was so fucking sad. nobody rly cared lol. "
        "Welcome to lephonk, the drippiest plugin on the market!",
        textRect.getX(), textRect.getY(), textRect.getWidth(), juce::Justification::centred);
}

void AboutWindow::resized()
{
}
