/*
  ==============================================================================

    MultiplierSlider.cpp
    Created: 13 Jan 2023 5:36:32pm
    Author:  thesp

  ==============================================================================
*/

#include <JuceHeader.h>
#include "MultiplierSlider.h"
#include "../../Common/Constants.h"

namespace xynth
{
MultiplierSlider::MultiplierSlider(xynth::GuiData& g) : guiData(g)
{
    setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);

    attach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
        g.audioProcessor.treeState, OTT_MULT_ID, *this);

    setRange(1.f, OTT_MULT_AMOUNT, 1.f);
}

void MultiplierSlider::paint(juce::Graphics& g)
{
    setMouseDragSensitivity(150 * getTransform().getScaleFactor());
    auto& lnf = guiData.getLnf();

    g.setColour(lnf.getBase1());
    g.fillRoundedRectangle(getLocalBounds().toFloat(), 4.f);

    g.setColour(lnf.getAccent1());
    g.setFont(16.f);
    g.drawText("x" + juce::String(getValue()), getLocalBounds(), juce::Justification::centred, false);
}

void MultiplierSlider::resized()
{
}

void MultiplierSlider::mouseEnter(const juce::MouseEvent& e)
{
    setMouseCursor(juce::MouseCursor::UpDownResizeCursor);
    juce::Slider::mouseEnter(e);
}

void MultiplierSlider::mouseExit(const juce::MouseEvent& e)
{
    setMouseCursor(juce::MouseCursor::NormalCursor);
    juce::Slider::mouseExit(e);
}
} // namespace xynth