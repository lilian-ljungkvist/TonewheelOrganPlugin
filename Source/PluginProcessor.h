/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "TonewheelWavetableOscillator.h"

struct DrawbarSettings
{
    int volume1{0};
    int volume2{0};
    int volume3{0};
    int volume4{0};
    int volume5{0};
    int volume6{0};
    int volume7{0};
    int volume8{0};
    int volume9{0};
    
};

DrawbarSettings getDrawBarSettings(juce::AudioProcessorValueTreeState& params);

struct Drawbar
{
    int volumeLevel;
    std::vector <TonewheelWavetableOscillator> oscillators;
    float harmonic;
};

//==============================================================================
/**
*/
class TonewheelOrganSynthAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    TonewheelOrganSynthAudioProcessor();
    ~TonewheelOrganSynthAudioProcessor() override;

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
    
    juce::AudioProcessorValueTreeState apvts;
    juce::AudioProcessorValueTreeState::ParameterLayout paramCreate();
    

private:
    
    Drawbar drawbarsArr[9];
    
    std::vector <float> generateSineWaveTable(Drawbar drawbar);
    void handleMidiEvent(const juce::MidiMessage& midiEvent);
    float midiNoteNumberToFrequency(int midiNoteNumber);
    void render(juce::AudioBuffer<float> &buffer, int startSample, int endSample);
    void updateDrawBarVolume();
    
    void initializeOscillators();
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TonewheelOrganSynthAudioProcessor)
};
