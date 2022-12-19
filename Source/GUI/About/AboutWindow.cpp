/*
  ==============================================================================

    AboutWindow.cpp
    Created: 8 Sep 2022 5:08:23pm
    Author:  thesp

  ==============================================================================
*/

#include <JuceHeader.h>
#include "AboutWindow.h"

AboutWindow::AboutWindow(xynth::GuiData& g) : guiData(g), siteButton(g), 
    updatesButton(g), backButton(g), updateChecker(g), downloadButton(g)
{
    initPaintFunctions();

    addAndMakeVisible(siteButton);
    addAndMakeVisible(updatesButton);
    addChildComponent(backButton);
    addChildComponent(downloadButton);

    xynthLogo = juce::ImageCache::getFromMemory(BinaryData::xynthLogo_png, BinaryData::xynthLogo_pngSize);

    siteButton.setText("Visit Website");
    siteButton.setFillIn(false);
    siteButton.onClick = []() { juce::URL("https://www.xynthaudio.com/plugins/lephonk").launchInDefaultBrowser(); };

    updatesButton.setText("Check Updates");
    updatesButton.onClick = [this]() {setState(updates); };

    downloadButton.setText("Latest Download");
    downloadButton.setFillIn(false);
    downloadButton.onClick = []() { juce::URL("https://app.gumroad.com/library").launchInDefaultBrowser(); };

    backButton.onClick = [this]() {setState(main); };

    updateChecker.updateCallback = [this](bool isUpdateAvailable)
    {
        DBG("Update callback");
        repaint();
    };
}

void AboutWindow::setState(const StatesEnum newState)
{
    state = newState;
    DBG("setState: " << newState);

    switch (state)
    {
    case main:
        siteButton    .setVisible(true);
        updatesButton .setVisible(true);
        backButton    .setVisible(false);
        downloadButton.setVisible(false);
        break;
    case updates:
        siteButton    .setVisible(false);
        updatesButton .setVisible(false);
        backButton    .setVisible(true);
        downloadButton.setVisible(true);
        updateChecker.checkForUpdates();
        break;
    }

    repaint();
}

void AboutWindow::initPaintFunctions()
{
    paintBackground = [this](juce::Graphics& g, juce::Rectangle<float>& rect, juce::CustomLook& lnf)
    {
        g.setColour(lnf.getBase1().darker());
        g.fillRoundedRectangle(rect, 8.f);
        g.setColour(lnf.getNeutral1());
        g.drawRoundedRectangle(rect.reduced(1.f), 8.f, 2.f);

        const int width = 32;
        g.setOpacity(0.9f);
        g.drawImageWithin(xynthLogo, rect.getWidth() - width - 32, 0, width, 60, juce::RectanglePlacement::xLeft);
    };

    paintMain = [this](juce::Graphics& g, juce::Rectangle<float>& rect, juce::CustomLook& lnf)
    {
        g.setColour(lnf.getAccent2());
        g.setFont(lnf.getCustomFontSemiBold());
        g.drawText("About Us", rect.removeFromTop(60.f), juce::Justification::centred);

        g.drawLine(30.f, rect.getY(), rect.getWidth() - 30.f, rect.getY(), 2.f);

        rect.removeFromTop(48.f);
        auto textRect = rect.reduced(20.f, 0.f);
        g.setColour(lnf.getNeutral1().brighter(1.f));
        g.setFont(lnf.getCustomFontRegular());
        g.drawMultiLineText("    Skybreak was born on Janurary 17th, 2019 and died on saturday. "
            "Did you know: he originally developed the first lephonk plugin? from paper "
            "skys brain, skybreak made a version then sharks made a version the speechrezz "
            "made the best version and sharks was so fucking sad. nobody rly cared lol.",
            textRect.getX(), textRect.getY(), textRect.getWidth());

        g.drawMultiLineText("Welcome to Le Phonk, the drippiest plugin on the market!",
            textRect.getX(), textRect.getY() + 212.f, textRect.getWidth(), juce::Justification::centred);

        auto versionRect = rect.reduced(20.f);
        juce::String version = JucePlugin_VersionString;
        g.setOpacity(0.6f);
        g.drawText("v" + version, versionRect.withTrimmedBottom(42).removeFromBottom(32), juce::Justification::bottomRight);
    };

    paintUpdates = [this](juce::Graphics& g, juce::Rectangle<float>& rect, juce::CustomLook& lnf)
    {
        g.setColour(lnf.getAccent2());
        g.setFont(lnf.getCustomFontSemiBold());
        g.drawText("Updates", rect.removeFromTop(60.f), juce::Justification::centred);

        g.drawLine(30.f, rect.getY(), rect.getWidth() - 30.f, rect.getY(), 2.f);

        const int updateState = updateChecker.getUpdateState();
        juce::String updateTitleText = "null";
        juce::String updateVersionText = "";
        switch (updateState)
        {
        case xynth::UpdateChecker::UpdateStates::checkingUpdate:
            updateTitleText = "Checking for updates...";
            break;

        case xynth::UpdateChecker::UpdateStates::noUpdateAvailable:
            updateTitleText = "You are up to date!";
            updateVersionText = "v" + updateChecker.getLatestVersion();
            break;

        case xynth::UpdateChecker::UpdateStates::updateAvailable:
            updateTitleText = "New update available!";
            updateVersionText = "v" + juce::String(JucePlugin_VersionString) +
                " -> v" + updateChecker.getLatestVersion();
            break;

        case xynth::UpdateChecker::UpdateStates::updateError:
            updateTitleText = "Something went wrong.";
            updateVersionText = "Error: " + updateChecker.getLatestVersion();
            break;
        }

        rect.removeFromTop(74.f);
        g.setColour(lnf.getNeutral1().brighter(1.f));
        g.setFont(lnf.getCustomFontMedium().withHeight(32.f));
        g.drawText(updateTitleText, rect.removeFromTop(32.f), juce::Justification::centred);

        rect.removeFromTop(4.f);
        g.setColour(lnf.getNeutral1().brighter(.4f));
        g.setFont(lnf.getCustomFontRegular().withHeight(20.f));
        g.drawText(updateVersionText, rect.removeFromTop(20.f), juce::Justification::centred);
    };

    paintStates = { paintMain, paintUpdates };
}

void AboutWindow::paint (juce::Graphics& g)
{
    auto rect = getLocalBounds().toFloat();
    auto& lnf = guiData.getLnf();

    paintBackground(g, rect, lnf);
    paintStates[state](g, rect, lnf);
}

void AboutWindow::resized()
{
    //serverCheck.checkForUpdates();

    auto mainRect = getLocalBounds().reduced(20);
    auto updatesRect = mainRect;
    updatesRect.removeFromTop(252);

    siteButton    .setBounds(mainRect.removeFromLeft (120).removeFromBottom(32));
    updatesButton .setBounds(mainRect.removeFromRight(124).removeFromBottom(32));
    downloadButton.setBounds(updatesRect.removeFromTop(32).withSizeKeepingCentre(150, 32));
    backButton    .setBounds(juce::Rectangle<int>(32, 0, 18, 60).withSizeKeepingCentre(18, 36));
}

