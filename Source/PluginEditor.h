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
    
    

    juce::Label levelSliderLabel;
    juce::Slider levelSlider;

    juce::Label feedbackSliderLabel;
    juce::Slider feedbackSlider;

    juce::Label DryWetSliderLabel;
    juce::Slider DryWetSlider;

    juce::Label  delayTimeSliderLabel;
    juce::Slider delayTimeSlider;

    void sliderValueChanged(juce::Slider* slider) override;

        
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CircularBufferDelayAudioProcessorEditor)
};

    
