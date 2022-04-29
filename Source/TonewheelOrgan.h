/*
  ==============================================================================

    TonewheelOrgan.h
    Created: 25 Apr 2022 7:25:29pm
    Author:  Lilian Ljungkvist

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "TonewheelWavetableOscillator.h"
class TonewheelOrgan
{
public:
    void prepareToPlay(double sampleRate);
    void processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages);
    void initializeOscillators();
//    void setReverbParams(float roomSize, float damping, float wetLevel, float dryLevel);
private:
    void handleMidiEvent(const juce::MidiMessage& midiEvent);
    void render(juce::AudioBuffer<float>& buffer, int startSample, int endSample);
    float midiNoteNumberToFrequency(int midiNoteNumber);
    double sampleRate;
//    std::vector <std::vector <TonewheelWavetableOscillator> > drawbarOscillators;
    std::vector <TonewheelWavetableOscillator> drawbarOscillators[9];//Make multiple oscillators for each drawbar in a vector
    std::vector <float> generateSineWaveTable(int drawBarId, int oscillatorId);
    juce::Reverb reverb;
    juce::ADSR envelope;
//    juce::Reverb::Parameters parameters;
};
