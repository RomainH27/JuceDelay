/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <cmath>

//==============================================================================
CircularBufferDelayAudioProcessorEditor::CircularBufferDelayAudioProcessorEditor (CircularBufferDelayAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    setSize (800, 250);

    

    setLookAndFeel(&test);
   

    levelSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    levelSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 60, 20);
    levelSlider.setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::white);
    levelSlider.setColour(juce::Slider::textBoxTextColourId, juce::Colours::grey);
    levelSlider.setRange(0.0, 1.0, 0.01);
    levelSlider.setValue(0.0);
    levelSlider.addListener(this);

    levelSliderLabel.setText("Volume", juce::dontSendNotification);
    levelSliderLabel.attachToComponent(&levelSlider, false);
    levelSliderLabel.setColour(juce::Label::textColourId, juce::Colours::grey);
    levelSliderLabel.setJustificationType(juce::Justification::centred);

    addAndMakeVisible(levelSlider);

    feedbackSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    feedbackSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 60, 20);
    feedbackSlider.setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::white);
    feedbackSlider.setColour(juce::Slider::textBoxTextColourId, juce::Colours::grey);
    feedbackSlider.setRange(0.0, 1.0, 0.01);
    feedbackSlider.setValue(0.0f);
    feedbackSlider.addListener(this);

    feedbackSliderLabel.setText("Feedback", juce::dontSendNotification);
    feedbackSliderLabel.attachToComponent(&feedbackSlider, false);
    feedbackSliderLabel.setColour(juce::Label::textColourId, juce::Colours::grey);
    feedbackSliderLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(feedbackSlider);

    delayTimeSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    delayTimeSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 60, 20);
    delayTimeSlider.setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::white);
    delayTimeSlider.setColour(juce::Slider::textBoxTextColourId, juce::Colours::grey);
    delayTimeSlider.setRange(0.0, 1.0, 0.01);
    delayTimeSlider.setValue(0.0f);
    delayTimeSlider.addListener(this);

    delayTimeSliderLabel.setText("Delay Time", juce::dontSendNotification);
    delayTimeSliderLabel.attachToComponent(&delayTimeSlider, false);
    delayTimeSliderLabel.setColour(juce::Label::textColourId, juce::Colours::grey);
    delayTimeSliderLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(delayTimeSlider);

    DryWetSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    DryWetSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 60, 20);
    DryWetSlider.setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::white);
    DryWetSlider.setColour(juce::Slider::textBoxTextColourId, juce::Colours::grey);
    DryWetSlider.setRange(0.0, 1.0, 0.01);
    DryWetSlider.setValue(0.0f);
    DryWetSlider.addListener(this);

    DryWetSliderLabel.setText("Dry/Wet", juce::dontSendNotification);
    DryWetSliderLabel.attachToComponent(&DryWetSlider, false);
    DryWetSliderLabel.setColour(juce::Label::textColourId, juce::Colours::grey);
    DryWetSliderLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(DryWetSlider); 

    /*
    group1.setText("Parameters");
    group1.setColour(juce::GroupComponent::outlineColourId, juce::Colours::grey);
    addAndMakeVisible(group1);*/
}

CircularBufferDelayAudioProcessorEditor::~CircularBufferDelayAudioProcessorEditor()
{
    setLookAndFeel(nullptr);
}

//==============================================================================
void CircularBufferDelayAudioProcessorEditor::paint (juce::Graphics& g)
{
    //g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    background = juce::ImageCache::getFromMemory(BinaryData::Frame_1_png, BinaryData::Frame_1_pngSize);
    g.drawImageWithin(background, 0, 0, getWidth(), getHeight(), juce::RectanglePlacement::stretchToFit);
}

void CircularBufferDelayAudioProcessorEditor::resized()
{
    delayTimeSlider.setBounds(40, getHeight() / 4, getWidth() / 5, getHeight() / 2);

    feedbackSlider.setBounds(65 + delayTimeSlider.getWidth(), getHeight() / 4, getWidth() / 5, getHeight() / 2);

    DryWetSlider.setBounds(90 + (delayTimeSlider.getWidth() * 2), getHeight() / 4, getWidth() / 5, getHeight() / 2);

    levelSlider.setBounds(115 + (delayTimeSlider.getWidth() * 3), getHeight() / 4, getWidth() / 5, getHeight() / 2);

    group1.setBounds(delayTimeSlider.getX(), delayTimeSlider.getY() - 50 , delayTimeSlider.getWidth() * 2 + 50 , delayTimeSlider.getHeight() + 70);

}

void CircularBufferDelayAudioProcessorEditor::sliderValueChanged(juce::Slider* slider)
{

    if (slider == &levelSlider) {

        audioProcessor.volume = levelSlider.getValue();
    }
    if (slider == &feedbackSlider) {

        audioProcessor.feedback = feedbackSlider.getValue();
    }
    if (slider == &DryWetSlider) {

        audioProcessor.dryWet = DryWetSlider.getValue();
    }
    if (slider == &delayTimeSlider) {

        audioProcessor.delayTime = delayTimeSlider.getValue();
    }
}

void  CustomLNF::drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos,
    const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider& slider)
{
    auto outline = slider.findColour(juce::Slider::rotarySliderOutlineColourId);
    auto fill = slider.findColour(juce::Slider::rotarySliderFillColourId);

    auto bounds = juce::Rectangle<int>(x, y, width, height).toFloat().reduced(10);

    auto radius = juce::jmin(bounds.getWidth(), bounds.getHeight()) / 2.0f;
    auto toAngle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
    auto lineW = 3.0f;
    auto arcRadius = radius - lineW * 0.5f;

    juce::Path backgroundArc;
    backgroundArc.addCentredArc(bounds.getCentreX(),
        bounds.getCentreY(),
        arcRadius,
        arcRadius,
        0.0f,
        rotaryStartAngle,
        rotaryEndAngle,
        true);

    g.setColour(juce::Colours::grey);
    g.strokePath(backgroundArc, juce::PathStrokeType(lineW, juce::PathStrokeType::curved, juce::PathStrokeType::rounded));

    if (slider.isEnabled())
    {
        juce::Path valueArc;
        valueArc.addCentredArc(bounds.getCentreX(),
            bounds.getCentreY(),
            arcRadius,
            arcRadius,
            0.0f,
            rotaryStartAngle,
            toAngle,
            true);

        g.setColour(juce::Colours::grey);
        g.strokePath(valueArc, juce::PathStrokeType(lineW, juce::PathStrokeType::curved, juce::PathStrokeType::rounded));
    }

    auto thumbWidth = lineW * 2.0f;
    juce::Point<float> thumbPoint(bounds.getCentreX() + arcRadius * std::cos(toAngle - juce::MathConstants<float>::halfPi),
        bounds.getCentreY() + arcRadius * std::sin(toAngle - juce::MathConstants<float>::halfPi));

    g.setColour(juce::Colours::grey);

    g.drawLine(thumbPoint.getX(), thumbPoint.getY() , bounds.getCentreX() + (arcRadius/2) * std::cos(toAngle - juce::MathConstants<float>::halfPi),
        bounds.getCentreY() + (arcRadius / 2) * std::sin(toAngle - juce::MathConstants<float>::halfPi), 3.0f);
}

