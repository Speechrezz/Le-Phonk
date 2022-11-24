/*
  ==============================================================================

    LogoButton.cpp
    Created: 8 Sep 2022 4:59:35pm
    Author:  thesp

  ==============================================================================
*/

#include <JuceHeader.h>
#include "LogoButton.h"

LogoButton::LogoButton(xynth::GuiData& g) : guiData(g)
{

}

LogoButton::~LogoButton()
{
}

void LogoButton::paint (juce::Graphics& g)
{
}

void LogoButton::resized()
{
}

void LogoButton::mouseDown(const juce::MouseEvent& e)
{
    guiData.showAbout();
}

void LogoButton::mouseEnter(const juce::MouseEvent& e)
{
    setMouseCursor(juce::MouseCursor::PointingHandCursor);
    juce::Component::mouseEnter(e);
}

void LogoButton::mouseExit(const juce::MouseEvent& e)
{
    setMouseCursor(juce::MouseCursor::NormalCursor);
    juce::Component::mouseExit(e);
}
