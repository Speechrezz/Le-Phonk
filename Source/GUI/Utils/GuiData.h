/*
  ==============================================================================

    GuiData.h
    Created: 5 Sep 2022 3:56:01pm
    Author:  thesp

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "../../PluginProcessor.h"
#include "../CustomLooks/CustomLook.h"
#include "../CustomLooks/HellLook.h"
#include "../CustomLooks/JuiceLook.h"
#include "../CustomLooks/DrippyLook.h"

namespace xynth
{
struct DefaultLookAndFeel
{
    DefaultLookAndFeel()  { juce::LookAndFeel::setDefaultLookAndFeel(lnf);    }
    ~DefaultLookAndFeel() { juce::LookAndFeel::setDefaultLookAndFeel(nullptr); }

    void updateLnf() { juce::LookAndFeel::setDefaultLookAndFeel(lnf); }

    juce::HellLook   hellLook;
    juce::JuiceLook  juiceLook;
    juce::DrippyLook drippyLook;

    // Change to desired LookAndFeel
    juce::CustomLook* lnf = &hellLook;
};

struct GuiData
{
    GuiData(LePhonkAudioProcessor& p, DefaultLookAndFeel& defLnf, double& s, juce::ApplicationProperties& props)
        : audioProcessor(p), scale(s), defaultLnf(defLnf), properties(props) 
    {}

    void updateLnf(int skin) 
    { 
        if (skin == hell)
            defaultLnf.lnf = &defaultLnf.hellLook;
        else if (skin == juice)
            defaultLnf.lnf = &defaultLnf.juiceLook;
        else if (skin == drippy)
            defaultLnf.lnf = &defaultLnf.drippyLook;
        else
            jassertfalse; // wrong index (too many items?)

        defaultLnf.updateLnf(); 

        properties.getUserSettings()->setValue("Skin", skin);
        properties.saveIfNeeded();
    }

    LePhonkAudioProcessor& audioProcessor;
    double& scale;
    DefaultLookAndFeel& defaultLnf;
    juce::ApplicationProperties& properties;

    juce::CustomLook& getLnf() { return *defaultLnf.lnf; }
    std::function<void()> showAbout;
    std::function<void()> showUpdates;

    // Global tooltip functions
    std::function<void(juce::Component*, const juce::String& prefixText)> showTooltip;
    std::function<void(const juce::String& newValue)> updateTooltipValue;
    std::function<void()> hideTooltip;

private:
    enum skinEnum { hell, juice, drippy };

};
} //namespace xynth