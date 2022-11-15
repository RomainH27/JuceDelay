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
    
    setSize (400, 600);


    levelSLider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalDrag);
    levelSLider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 75, 75);
    levelSLider.setRange(0.0f, 1.0f);
    levelSLider.setValue(0.5f);
    levelSLider.addListener(this);
    addAndMakeVisible(levelSLider);
}

CircularBufferDelayAudioProcessorEditor::~CircularBufferDelayAudioProcessorEditor()
{
}

//==============================================================================
void CircularBufferDelayAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

}

void CircularBufferDelayAudioProcessorEditor::resized()
{
    levelSLider.setBounds(getLocalBounds()/2);
}

void CircularBufferDelayAudioProcessorEditor::sliderValueChanged(juce::Slider* slider) {

    if (slider == &levelSLider) {

        audioProcessor.volume = levelSLider.getValue();
    }
}