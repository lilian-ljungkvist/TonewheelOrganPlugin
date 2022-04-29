/*
  ==============================================================================

    TonewheelOrgan.cpp
    Created: 25 Apr 2022 7:25:29pm
    Author:  Lilian Ljungkvist
 
    REFERENCED CODE:
    WolfSound Wavetable synth tutorial:https://www.youtube.com/watch?v=Ah4P-zOfdYc
    Juce Docs Wavetable synth tutorial:https://docs.juce.com/master/tutorial_wavetable_synth.html

  ==============================================================================
*/

#include "TonewheelOrgan.h"
void TonewheelOrgan::prepareToPlay(double sampleRate)
{
    this->sampleRate = sampleRate; //Get the sample rate passed in and assign it to variable
    reverb.reset();
    envelope.reset();
    initializeOscillators();
    reverb.setParameters(juce::Reverb::Parameters({0.3,0.2,0.2,0.2,1}));
    reverb.setSampleRate(sampleRate);
    envelope.setParameters(juce::ADSR::Parameters({0.08,0.2,0.5,0.2}));
    envelope.setSampleRate(sampleRate);
   
}
void TonewheelOrgan::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    auto currentSample = 0;
    
    for(const auto midiMessage : midiMessages)
    {
        const auto midiEvent = midiMessage.getMessage(); //Get each MIDI message
        const auto midiEventSample = static_cast <int> (midiEvent.getTimeStamp()); //Get each sample from MIDI message
        
        render(buffer, currentSample, midiEventSample);
        handleMidiEvent(midiEvent);
        
        currentSample = midiEventSample;
    }
    render(buffer, currentSample, buffer.getNumSamples());

}
void TonewheelOrgan::handleMidiEvent(const juce::MidiMessage& midiEvent)
{
    for(auto& drawbar : drawbarOscillators) //Go through each drawbar
    {
//        for(auto& oscillator : drawbar)
//        {
//            //Called when key was pressed or key was released etc..
            if(midiEvent.isNoteOn())
            {
                const auto oscillatorId = midiEvent.getNoteNumber(); //Gets note for oscillator from MIDI event
                const auto frequency = midiNoteNumberToFrequency(oscillatorId);
                drawbarOscillators[0][oscillatorId].setFrequency(frequency); //Set Oscillator to the frequency of the MIDI note played
                envelope.noteOn();
                
            }
            if(midiEvent.isNoteOff())
            {
                const auto oscillatorId = midiEvent.getNoteNumber();
                
                drawbarOscillators[0][oscillatorId].stop();
                
                envelope.noteOff();
                
            }
            if(midiEvent.isAllNotesOff())
            {
             
                    for(auto& oscillator : drawbar)
                    {
                        oscillator.stop();
                    }
        
            }
//        }
    }
    
}
float TonewheelOrgan::midiNoteNumberToFrequency(int midiNoteNumber)
{
    constexpr auto A4_FREQUENCY = 440.f; //Fundamental frequency
    constexpr auto A4_NOTE_NUMBER = 69.f; //
    constexpr auto SEMITONES_IN_AN_OCTAVE = 12.f;
    
    return A4_FREQUENCY * std::powf(2.f, (midiNoteNumber - A4_NOTE_NUMBER) / SEMITONES_IN_AN_OCTAVE);
    //Fundamental frequency shifted relative to its position
    //Subtract the A4 note number from the midi note number to get the absolute difference
   // 2^(difference in semitones)
}

void TonewheelOrgan::initializeOscillators()
{
    constexpr auto OSCILLATORS_PER_DRAWBAR= 128;
//    const auto wavetable = generateSineWaveTable(2);
    for(auto i = 0; i < juce::numElementsInArray(drawbarOscillators); i++) //Go through each drawbar
    {
        drawbarOscillators[i].clear();

        for(auto j = 0; j < OSCILLATORS_PER_DRAWBAR; j++)
        {
            drawbarOscillators[i].emplace_back(generateSineWaveTable(i, j), sampleRate);
        }
    }

}

std::vector <float> TonewheelOrgan::generateSineWaveTable(int drawbarId, int oscillatorId)
{
    constexpr auto WAVETABLE_LENGTH = 64;
    
    std::vector <float> sineWaveTable(WAVETABLE_LENGTH);
  
        auto angleDelta = juce::MathConstants<double>::twoPi / (double) (WAVETABLE_LENGTH - 1);
//        auto angleDelta = juce::MathConstants<double>::twoPi;
        auto currAngle = 0.0;
//        int numVoices = drawbar.length;
//        int harmonic = drawbar.register;
        for(auto i = 0; i < WAVETABLE_LENGTH; i++)
        {
//            sineWaveTable[i] = std::cosf(std::sinf(currAngle) + std::sinf(currAngle * 2) + std::sinf(currAngle * 4)+ std::sinf(currAngle * 6))/4;
            
//            sineWaveTable[i] = (std::sinf(currAngle) + std::sinf(currAngle * 2) + std::sinf(currAngle * 4))/3;
            
            
            sineWaveTable[i] = (std::sinf(currAngle) + std::sinf(currAngle * 2) + std::sinf(currAngle * 3))/3;

            
//            sineWaveTable[i] = std::sinf(currAngle);
            currAngle += angleDelta;
        }
    return sineWaveTable;
}

void TonewheelOrgan::render(juce::AudioBuffer<float> &buffer, int startSample, int endSample)
{
    auto * firstChannel = buffer.getWritePointer(0);
    for(auto& drawbar : drawbarOscillators) //Go through each drawbar
    {
        for(auto& oscillator : drawbar) //Each oscillator in the drawbar
        {
            if(oscillator.isPlaying())
            {
                for(auto sample = startSample; sample < endSample; sample++)
                {
                    firstChannel[sample] += oscillator.getSample(); //Add each sample from the oscillator to channel buffer
                }
            }
        }
    }
    for(auto channel = 1; channel < buffer.getNumChannels(); channel++)
    {
        std::copy(firstChannel + startSample, firstChannel + endSample, buffer.getWritePointer(channel) + startSample); //Copy first channel to all channels
    }
    reverb.processMono(firstChannel, buffer.getNumSamples());
    envelope.applyEnvelopeToBuffer (buffer, 0, buffer.getNumSamples());


}

//void TonewheelOrgan::setReverbParams(float roomSize, float damping, float wetLevel, float dryLevel)
//{
//  reverb.setParameters(<#const Parameters &newParams#>)
//}
