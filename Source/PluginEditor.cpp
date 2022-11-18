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
    levelSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 60, 20);
    levelSlider.setRange(0.0f, 1.0f);
    levelSlider.setValue(0.0f);
    levelSlider.addListener(this);

    levelSliderLabel.setText("Volume", juce::dontSendNotification);
    levelSliderLabel.attachToComponent(&levelSlider, false);
    levelSliderLabel.setJustificationType(juce::Justification::centred);

    levelSliderValue.setText("0.00", juce::dontSendNotification);
 
    addAndMakeVisible(levelSliderValue);
   
   // levelSliderValue.attachToComponent(&levelSlider, false);

    addAndMakeVisible(levelSlider);

    feedbackSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    feedbackSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 60, 20);
    feedbackSlider.setRange(0.0f, 1.0f);
    feedbackSlider.setValue(0.0f);
    feedbackSlider.addListener(this);
    feedbackSliderLabel.setText("Feedback", juce::dontSendNotification);
    feedbackSliderLabel.attachToComponent(&feedbackSlider, false);
    addAndMakeVisible(feedbackSlider);

    delayTimeSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    delayTimeSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 60, 20);
    delayTimeSlider.setRange(0.0f, 1.0f);
    delayTimeSlider.setValue(0.0f);
    delayTimeSlider.addListener(this);
    delayTimeSliderLabel.setText("Delay Time", juce::dontSendNotification);
    delayTimeSliderLabel.attachToComponent(&delayTimeSlider, false);
    addAndMakeVisible(feedbackSlider);
    addAndMakeVisible(delayTimeSlider);

    DryWetSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    DryWetSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 60, 20);
    DryWetSlider.setRange(0.0f, 1.0f);
    DryWetSlider.setValue(0.0f);
    DryWetSlider.addListener(this);
    DryWetSliderLabel.setText("Dry/Wet", juce::dontSendNotification);
    DryWetSliderLabel.attachToComponent(&DryWetSlider, false);
    addAndMakeVisible(DryWetSlider);
}

CircularBufferDelayAudioProcessorEditor::~CircularBufferDelayAudioProcessorEditor()
{
    setLookAndFeel(nullptr);
}

//==============================================================================
void CircularBufferDelayAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

}

void CircularBufferDelayAudioProcessorEditor::resized()
{
    levelSlider.setBounds(40, getHeight() / 4,getWidth()/5, getHeight() / 2);

    levelSliderValue.setBounds(40 + levelSlider.getWidth() /2.5 , getHeight() / 4, getWidth() / 10, getHeight() / 2);

    feedbackSlider.setBounds(65+levelSlider.getWidth(), getHeight() / 4, getWidth() / 5, getHeight() / 2);
    DryWetSlider.setBounds(90 + (levelSlider.getWidth()*2), getHeight() / 4, getWidth() / 5, getHeight() / 2);
    delayTimeSlider.setBounds(115 + (levelSlider.getWidth() * 3), getHeight() / 4, getWidth() / 5, getHeight() / 2);
}

void CircularBufferDelayAudioProcessorEditor::sliderValueChanged(juce::Slider* slider)
{
    std::cout << std::setprecision(1);


    if (slider == &levelSlider) {
        

        float value = levelSlider.getValue();
        
        audioProcessor.volume = levelSlider.getValue();
        levelSliderValue.setText(std::to_string(value), juce::dontSendNotification);
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

    g.setColour(juce::Colours::white);
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

        g.setColour(juce::Colours::white);
        g.strokePath(valueArc, juce::PathStrokeType(lineW, juce::PathStrokeType::curved, juce::PathStrokeType::rounded));
    }

    auto thumbWidth = lineW * 2.0f;
    juce::Point<float> thumbPoint(bounds.getCentreX() + arcRadius * std::cos(toAngle - juce::MathConstants<float>::halfPi),
        bounds.getCentreY() + arcRadius * std::sin(toAngle - juce::MathConstants<float>::halfPi));

    g.setColour(juce::Colours::white);

    g.drawLine(thumbPoint.getX(), thumbPoint.getY() , bounds.getCentreX() + (arcRadius/2) * std::cos(toAngle - juce::MathConstants<float>::halfPi),
        bounds.getCentreY() + (arcRadius / 2) * std::sin(toAngle - juce::MathConstants<float>::halfPi), 3.0f);
}

