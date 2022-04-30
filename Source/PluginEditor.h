/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "TonewheelOrgan.h"

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
    TonewheelOrgan organ;
    
    juce::Slider drawbarSliders[9]; //9 Sliders for controlling Drawbars volume
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> volume1;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> volume2;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> volume3;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> volume4;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> volume5;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> volume6;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> volume7;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> volume8;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> volume9;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TonewheelAudioProcessorEditor);
};
