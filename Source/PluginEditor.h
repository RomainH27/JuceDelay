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

    juce::Label sliderLabel;
    juce::Slider levelSLider;

    void sliderValueChanged(juce::Slider* slider) override;
        
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CircularBufferDelayAudioProcessorEditor)
};
