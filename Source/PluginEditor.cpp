/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
CircularBufferDelayAudioProcessorEditor::CircularBufferDelayAudioProcessorEditor (CircularBufferDelayAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    setSize (800, 250);


    levelSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    levelSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 60, 20);
    levelSlider.setRange(0.0f, 1.0f);
    levelSlider.setValue(0.5f);
    levelSlider.addListener(this);

    levelSliderLabel.setText("Volume", juce::dontSendNotification);
    levelSliderLabel.attachToComponent(&levelSlider, false);
    addAndMakeVisible(levelSlider);

    feedbackSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    feedbackSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 60, 20);
    feedbackSlider.setRange(0.0f, 1.0f);
    feedbackSlider.setValue(0.5f);
    feedbackSlider.addListener(this);
    feedbackSliderLabel.setText("Feedback", juce::dontSendNotification);
    feedbackSliderLabel.attachToComponent(&feedbackSlider, false);
    addAndMakeVisible(feedbackSlider);

    delayTimeSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    delayTimeSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 60, 20);
    delayTimeSlider.setRange(0.0f, 1.0f);
    delayTimeSlider.setValue(0.5f);
    delayTimeSlider.addListener(this);
    delayTimeSliderLabel.setText("Delay Time", juce::dontSendNotification);
    delayTimeSliderLabel.attachToComponent(&delayTimeSlider, false);
    addAndMakeVisible(feedbackSlider);
    addAndMakeVisible(delayTimeSlider);

    DryWetSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    DryWetSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 60, 20);
    DryWetSlider.setRange(0.0f, 1.0f);
    DryWetSlider.setValue(0.5f);
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
    feedbackSlider.setBounds(65+levelSlider.getWidth(), getHeight() / 4, getWidth() / 5, getHeight() / 2);
    DryWetSlider.setBounds(90 + (levelSlider.getWidth()*2), getHeight() / 4, getWidth() / 5, getHeight() / 2);
    delayTimeSlider.setBounds(115 + (levelSlider.getWidth() * 3), getHeight() / 4, getWidth() / 5, getHeight() / 2);
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


