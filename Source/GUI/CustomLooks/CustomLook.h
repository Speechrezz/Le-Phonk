/*
  ==============================================================================

    CustomLook.h
    Created: 5 Sep 2022 5:10:46pm
    Author:  thesp

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

namespace juce
{
class CustomLook : public LookAndFeel_V4
{
public:
    CustomLook();

    // For debugging
    virtual String getLnfName() { return "CustomLook"; }

    // Custom draws
    virtual void drawSectionBackground(Graphics& g, Rectangle<int> area);
    virtual void drawDistGraphBackground(Graphics& g, Rectangle<float> area, float amplitude);
    virtual void drawDistGraphForeground(Graphics& g, Rectangle<float> area);
    virtual Image& getBackgroundImage() { return bgImage; };

    //==============================================================================
    // Sliders and buttons
    void drawCornerResizer(Graphics& g, int w, int h, bool, bool) override;

    void drawRotarySlider(Graphics&, int x, int y, int width, int height, float sliderPosProportional,
        float rotaryStartAngle, float rotaryEndAngle, Slider&) override;

    void drawLinearSlider(Graphics& g, int x, int y, int width, int height, float sliderPos,
        float minSliderPos, float maxSliderPos, const Slider::SliderStyle style, Slider& slider) override;

    void drawToggleButton(Graphics&, ToggleButton&,
        bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override;

    //==============================================================================
    // Drop down menu
    void drawComboBox(Graphics&, int width, int height, bool isButtonDown,
        int buttonX, int buttonY, int buttonW, int buttonH,
        ComboBox&) override;
    Font getComboBoxFont(ComboBox&) override;
    void positionComboBoxText(ComboBox&, Label&) override;

    //==============================================================================
    // Popup Menu
    void drawPopupMenuItem(Graphics&, const Rectangle<int>& area,
        bool isSeparator, bool isActive, bool isHighlighted, bool isTicked, bool hasSubMenu,
        const String& text, const String& shortcutKeyText,
        const Drawable* icon, const Colour* textColour) override;

    void drawPopupMenuBackground(Graphics& g, int width, int height) override;

    //==============================================================================
    // Fonts and colours
    virtual Colour getAccent1()  { return Colours::white; };
    virtual Colour getAccent2()  { return Colours::white; };
    virtual Colour getNeutral1() { return Colours::grey;  };
    virtual Colour getBase1()    { return Colours::black; };

    virtual const juce::Font getCustomFontRegular();
    virtual const juce::Font getCustomFontMedium();
    virtual const juce::Font getCustomFontSemiBold();
    virtual const juce::Font getCustomFontBold();

private:
    Image bgImage;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CustomLook)
};
} // namespace juce