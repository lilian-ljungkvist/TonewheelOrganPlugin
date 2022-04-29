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
class TonewheelAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    TonewheelAudioProcessorEditor (TonewheelAudioProcessor&);
    ~TonewheelAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    TonewheelAudioProcessor& audioProcessor;
    juce::Slider DrawbarSliders[9]; //9 Sliders for Drawbars

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TonewheelAudioProcessorEditor)
};
