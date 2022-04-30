/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "TonewheelOrgan.h"



struct DrawbarSettings
{
    float volume1{0};
    float volume2{0};
    float volume3{0};
    float volume4{0};
    float volume5{0};
    float volume6{0};
    float volume7{0};
    float volume8{0};
    float volume9{0};
    
};

DrawbarSettings getDrawBarSettings(juce::AudioProcessorValueTreeState& params);

//==============================================================================
/**
*/
class TonewheelAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    TonewheelAudioProcessor();
    ~TonewheelAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    static juce::AudioProcessorValueTreeState::ParameterLayout paramCreate();
    juce::AudioProcessorValueTreeState apvts{*this, nullptr, "Parameters", paramCreate()};


private:
    TonewheelOrgan organ;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TonewheelAudioProcessor)
};

