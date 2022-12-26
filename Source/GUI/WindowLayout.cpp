/*
  ==============================================================================

    WindowLayout.cpp
    Created: 5 Sep 2022 3:26:44pm
    Author:  thesp

  ==============================================================================
*/

#include <JuceHeader.h>
#include "WindowLayout.h"

WindowLayout::WindowLayout(xynth::GuiData& g) : guiData(g), zeketeLayout(g), ottzLayout(g), 
    fonzLayout(g), bypassGain(g), skinSelect(g), logoButton(g), aboutOverlay(g), tooltip(g)
{
    auto& treeState = g.audioProcessor.treeState;

    addAndMakeVisible(zeketeLayout);
    addAndMakeVisible(ottzLayout);
    addAndMakeVisible(fonzLayout);
    addAndMakeVisible(bypassGain);
    addAndMakeVisible(skinSelect);
    addAndMakeVisible(logoButton);
    addChildComponent(aboutOverlay);
    addChildComponent(tooltip);

    // --Show about/updates page--
    guiData.showAbout = [this]() 
    { 
        aboutOverlay.opened();
        aboutOverlay.setVisible(true); 
    };

    guiData.showUpdates = [this]()
    {
        aboutOverlay.openUpdatesMenu();
        aboutOverlay.setVisible(true);
    };

    // --Tooltip stuff--
    guiData.showTooltip = [this](juce::Component* component)
    {
        auto componentPosition = component->getScreenPosition();
        auto relativePosition = componentPosition - getScreenPosition();
        const auto scale = getTransform().getScaleFactor();
        relativePosition /= scale;
        relativePosition.addXY(component->getWidth() / 2, component->getHeight() + 2);
        tooltip.showTooltip(relativePosition);
    };

    guiData.updateTooltipText = [this](const juce::String& newText)
    {
        tooltip.updateTooltipText(newText);
    };

    guiData.hideTooltip = [this]()
    {
        tooltip.hideTooltip();
    };
}

void WindowLayout::paint (juce::Graphics& g)
{
    auto rect = getLocalBounds();

    g.drawImageWithin(guiData.getLnf().getBackgroundImage(), rect.getX(), rect.getY(), 
        rect.getWidth(), rect.getHeight(), juce::RectanglePlacement::fillDestination);
}

void WindowLayout::resized()
{
    const int spacing = 18;

    auto rect = getLocalBounds();
    auto headerRect = rect.removeFromTop(130).withTrimmedBottom(25).reduced(29, 0);
    rect.reduce(58, 0);

    zeketeLayout.setBounds(rect.removeFromTop(354));
    rect.removeFromTop(spacing);
    ottzLayout.setBounds(rect.removeFromTop(129));
    rect.removeFromTop(spacing);
    fonzLayout.setBounds(rect.removeFromTop(129));

    bypassGain.setBounds(headerRect.removeFromBottom(44).removeFromRight(54));

    skinSelect.setBounds(headerRect.removeFromRight(114)
        .withTrimmedTop(8).withSizeKeepingCentre(114, 30));

    logoButton.setBounds(headerRect.removeFromLeft(154).withTrimmedTop(10).translated(-8, 0));

    aboutOverlay.setBounds(getLocalBounds());
}
