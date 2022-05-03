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
class TonewheelOrganSynthAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    TonewheelOrganSynthAudioProcessorEditor (TonewheelOrganSynthAudioProcessor&);
    ~TonewheelOrganSynthAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
private:

    juce::Slider drawbarSliders[9];

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> drawbarOneGainAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> drawbarTwoGainAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> drawbarThreeGainAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> drawbarFourGainAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> drawbarFiveGainAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> drawbarSixGainAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> drawbarSevenGainAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> drawbarEightGainAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> drawbarNineGainAttachment;
    
    TonewheelOrganSynthAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TonewheelOrganSynthAudioProcessorEditor)
};
