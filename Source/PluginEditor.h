/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/

class CustomLNF : public juce::LookAndFeel_V4 {

public:
    void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos,
        const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider& slider) override;

};



class CircularBufferDelayAudioProcessorEditor  : public juce::AudioProcessorEditor,
    public juce::Slider::Listener
{
public:
    CircularBufferDelayAudioProcessorEditor (CircularBufferDelayAudioProcessor&);
    ~CircularBufferDelayAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
   


private:
    
    CircularBufferDelayAudioProcessor& audioProcessor;

    CustomLNF test;

    juce::Label levelSliderLabel;
    juce::Slider levelSlider;
    juce::Label levelSliderValue;

    juce::Label feedbackSliderLabel;
    juce::Slider feedbackSlider;

    juce::Label DryWetSliderLabel;
    juce::Slider DryWetSlider;

    juce::Label  delayTimeSliderLabel;
    juce::Slider delayTimeSlider;

    juce::GroupComponent group1;

    juce::Image background;

    void sliderValueChanged(juce::Slider* slider) override;

        
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CircularBufferDelayAudioProcessorEditor)
};


