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
    int sliderVolumes[9];
private:

//    juce::Slider drawbarOneGain;
    juce::Slider drawbarSliders[9];
//    juce::ScopedPointer<juce::AudioProcessorValueTreeState::SliderAttachment> drawbarOneGainAttachment;
//    juce::ScopedPointer<juce::AudioProcessorValueTreeState::SliderAttachment> drawbarTwoGainAttachment;
//    juce::ScopedPointer<juce::AudioProcessorValueTreeState::SliderAttachment> drawbarThreeGainAttachment;
//    juce::ScopedPointer<juce::AudioProcessorValueTreeState::SliderAttachment> drawbarFourGainAttachment;
//    juce::ScopedPointer<juce::AudioProcessorValueTreeState::SliderAttachment> drawbarFiveGainAttachment;
//    juce::ScopedPointer<juce::AudioProcessorValueTreeState::SliderAttachment> drawbarSixGainAttachment;
//    juce::ScopedPointer<juce::AudioProcessorValueTreeState::SliderAttachment> drawbarSevenGainAttachment;
//    juce::ScopedPointer<juce::AudioProcessorValueTreeState::SliderAttachment> drawbarEightGainAttachment;
//    juce::ScopedPointer<juce::AudioProcessorValueTreeState::SliderAttachment> drawbarNineGainAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> drawbarOneGainAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> drawbarTwoGainAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> drawbarThreeGainAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> drawbarFourGainAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> drawbarFiveGainAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> drawbarSixGainAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> drawbarSevenGainAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> drawbarEightGainAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> drawbarNineGainAttachment;




//    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> ;



    
    TonewheelOrganSynthAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TonewheelOrganSynthAudioProcessorEditor)
};
