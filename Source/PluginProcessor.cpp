/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <iostream>

//==============================================================================
TonewheelOrganSynthAudioProcessor::TonewheelOrganSynthAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), apvts (*this, nullptr, "Parameters", paramCreate())
#endif
{
    
}

TonewheelOrganSynthAudioProcessor::~TonewheelOrganSynthAudioProcessor()
{
}

//==============================================================================
const juce::String TonewheelOrganSynthAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool TonewheelOrganSynthAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool TonewheelOrganSynthAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool TonewheelOrganSynthAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double TonewheelOrganSynthAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int TonewheelOrganSynthAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int TonewheelOrganSynthAudioProcessor::getCurrentProgram()
{
    return 0;
}

void TonewheelOrganSynthAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String TonewheelOrganSynthAudioProcessor::getProgramName (int index)
{
    return {};
}

void TonewheelOrganSynthAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
    
}

//==============================================================================
void TonewheelOrganSynthAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
     
    drawbarsArr[0].harmonic = 0.5;
    drawbarsArr[1].harmonic = 0.33;
    drawbarsArr[2].harmonic = 1;
    drawbarsArr[3].harmonic = 2;
    drawbarsArr[4].harmonic = 3;
    drawbarsArr[5].harmonic = 4;
    drawbarsArr[6].harmonic = 5;
    drawbarsArr[7].harmonic = 6;
    drawbarsArr[8].harmonic = 8;
    
    drawbarsArr[0].volumeLevel = 0;
    drawbarsArr[1].volumeLevel = 0;
    drawbarsArr[2].volumeLevel = 0;
    drawbarsArr[3].volumeLevel = 0;
    drawbarsArr[4].volumeLevel = 0;
    drawbarsArr[5].volumeLevel = 0;
    drawbarsArr[6].volumeLevel = 0;
    drawbarsArr[7].volumeLevel = 0;
    drawbarsArr[8].volumeLevel = 0;
    
    initializeOscillators();
    updateDrawBarVolume();
}

void TonewheelOrganSynthAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool TonewheelOrganSynthAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif
juce::AudioProcessorValueTreeState::ParameterLayout TonewheelOrganSynthAudioProcessor::paramCreate()
{
//    juce::AudioProcessorValueTreeState::ParameterLayout params;
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;
//    params.add(std::make_unique<juce::AudioParameterInt>("DRAWBARGAIN1", "Drawbar 1 Gain", juce::NormalisableRange<float>(0.0f, 8.0f, 1.0f, 1.0f), 0.0f));
//    params.add(std::make_unique<juce::AudioParameterInt>("DRAWBARGAIN2", "Drawbar 2 Gain", juce::NormalisableRange<float>(0.0f, 8.0f, 1.0f, 1.0f), 0.0f));
//    params.add(std::make_unique<juce::AudioParameterInt>("DRAWBARGAIN3", "Drawbar 3 Gain", juce::NormalisableRange<float>(0.0f, 8.0f, 1.0f, 1.0f), 0.0f));
//    params.add(std::make_unique<juce::AudioParameterInt>("DRAWBARGAIN4", "Drawbar 4 Gain", juce::NormalisableRange<float>(0.0f, 8.0f, 1.0f, 1.0f), 0.0f));
//    params.add(std::make_unique<juce::AudioParameterInt>("DRAWBARGAIN5", "Drawbar 5 Gain", juce::NormalisableRange<float>(0.0f, 8.0f, 1.0f, 1.0f), 0.0f));
//    params.add(std::make_unique<juce::AudioParameterInt>("DRAWBARGAIN6", "Drawbar 6 Gain", juce::NormalisableRange<float>(0.0f, 8.0f, 1.0f, 1.0f), 0.0f));
//    params.add(std::make_unique<juce::AudioParameterInt>("DRAWBARGAIN7", "Drawbar 7 Gain", juce::NormalisableRange<float>(0.0f, 8.0f, 1.0f, 1.0f), 0.0f));
//    params.add(std::make_unique<juce::AudioParameterInt>("DRAWBARGAIN8", "Drawbar 8 Gain", juce::NormalisableRange<float>(0.0f, 8.0f, 1.0f, 1.0f), 0.0f));
//    params.add(std::make_unique<juce::AudioParameterInt>("DRAWBARGAIN9", "Drawbar 9 Gain", juce::NormalisableRange<float>(0.0f, 8.0f, 1.0f, 1.0f), 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterInt>("DRAWBARGAIN1", "Drawbar 1 Gain", 0,8,1));
    params.push_back(std::make_unique<juce::AudioParameterInt>("DRAWBARGAIN2", "Drawbar 2 Gain", 0,8,1));
    params.push_back(std::make_unique<juce::AudioParameterInt>("DRAWBARGAIN3", "Drawbar 3 Gain", 0,8,1));
    params.push_back(std::make_unique<juce::AudioParameterInt>("DRAWBARGAIN4", "Drawbar 4 Gain", 0,8,1));
    params.push_back(std::make_unique<juce::AudioParameterInt>("DRAWBARGAIN5", "Drawbar 5 Gain", 0,8,1));
    params.push_back(std::make_unique<juce::AudioParameterInt>("DRAWBARGAIN6", "Drawbar 6 Gain", 0,8,1));
    params.push_back(std::make_unique<juce::AudioParameterInt>("DRAWBARGAIN7", "Drawbar 7 Gain", 0,8,1));
    params.push_back(std::make_unique<juce::AudioParameterInt>("DRAWBARGAIN8", "Drawbar 8 Gain", 0,8,1));
    params.push_back(std::make_unique<juce::AudioParameterInt>("DRAWBARGAIN9", "Drawbar 9 Gain", 0,8,1));
    
//    return params;
    return {params.begin(),params.end()};
    
}

void TonewheelOrganSynthAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    
  
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    auto currentSample = 0;

    for(const auto midiMessage : midiMessages)
    {
        const auto midiEvent = midiMessage.getMessage(); //Get each MIDI message
        const auto midiEventSample = static_cast <int> (midiEvent.getTimeStamp()); //Get each sample from MIDI message
        
        render(buffer, currentSample, midiEventSample);
        handleMidiEvent(midiEvent);
        
        currentSample = midiEventSample;
    }

//    initializeOscillators();
    render(buffer, currentSample, buffer.getNumSamples());
    
    
    updateDrawBarVolume();
    
}

void TonewheelOrganSynthAudioProcessor::initializeOscillators()
{
    int numOscillators = 128;//Number of keys
    for(auto& drawbar : drawbarsArr) //Go through each drawbar
    {
        drawbar.oscillators.clear();
        for(auto j = 0; j < numOscillators; j++)
        {
        drawbar.oscillators.emplace_back(generateSineWaveTable(drawbar),getSampleRate());
        }
    }

}

void TonewheelOrganSynthAudioProcessor::updateDrawBarVolume()
{
    auto settings = getDrawBarSettings(apvts);
    
    drawbarsArr[0].volumeLevel = settings.volume1;
    drawbarsArr[1].volumeLevel = settings.volume2;
    drawbarsArr[2].volumeLevel = settings.volume3;
    drawbarsArr[3].volumeLevel = settings.volume4;
    drawbarsArr[4].volumeLevel = settings.volume5;
    drawbarsArr[5].volumeLevel = settings.volume6;
    drawbarsArr[6].volumeLevel = settings.volume7;
    drawbarsArr[7].volumeLevel = settings.volume8;
    drawbarsArr[8].volumeLevel = settings.volume9;
    
//    for(auto& drawbar : drawbarsArr)
//    {
//        std::cout<<"drawbar.volumeLevel: "<<drawbar.volumeLevel<<std::endl;
//    }
    

        
}

//==============================================================================
bool TonewheelOrganSynthAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* TonewheelOrganSynthAudioProcessor::createEditor()
{
    return new TonewheelOrganSynthAudioProcessorEditor (*this);
}

//==============================================================================
void TonewheelOrganSynthAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void TonewheelOrganSynthAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new TonewheelOrganSynthAudioProcessor();
}


DrawbarSettings getDrawBarSettings(juce::AudioProcessorValueTreeState& params)
{
 
    DrawbarSettings settings;
    
 
    
    settings.volume1 = params.getRawParameterValue("DRAWBARGAIN1")->load();
    settings.volume2 = params.getRawParameterValue("DRAWBARGAIN2")->load();
    settings.volume3 = params.getRawParameterValue("DRAWBARGAIN3")->load();
    settings.volume4 = params.getRawParameterValue("DRAWBARGAIN4")->load();
    settings.volume5 = params.getRawParameterValue("DRAWBARGAIN5")->load();
    settings.volume6 = params.getRawParameterValue("DRAWBARGAIN6")->load();
    settings.volume7 = params.getRawParameterValue("DRAWBARGAIN7")->load();
    settings.volume8 = params.getRawParameterValue("DRAWBARGAIN8")->load();
    settings.volume9 = params.getRawParameterValue("DRAWBARGAIN9")->load();
    
//    std::cout<<"settings.volume1: "<<settings.volume1<<"  settings.volume2: "<<settings.volume2<<"  settings.volume3: "<<settings.volume3<<"  settings.volume4: "<<settings.volume4<<"settings.volume5: "<<settings.volume5<<"  settings.volume6: "<<settings.volume6<<"  settings.volume7: "<<settings.volume7<<"  settings.volume8: "<<settings.volume8<<"  settings.volume9: "<<settings.volume9<<std::endl;
    return settings;
}

std::vector <float>  TonewheelOrganSynthAudioProcessor::generateSineWaveTable(Drawbar drawbar)
{
    constexpr auto WAVETABLE_LENGTH = 64;
  
    std::vector <float> sineWaveTable(WAVETABLE_LENGTH);
      
        auto angleDelta = juce::MathConstants<double>::twoPi / (double) (WAVETABLE_LENGTH - 1);
        auto currAngle = 0.0;
        for(auto i = 0; i < WAVETABLE_LENGTH; i++)
        {
          
            sineWaveTable[i] = std::sinf(currAngle) + std::sinf(currAngle * static_cast<float>(drawbar.harmonic));

            currAngle += angleDelta;
        }
    return sineWaveTable;
}

void TonewheelOrganSynthAudioProcessor::handleMidiEvent(const juce::MidiMessage& midiEvent)
{
    for(auto& drawbar : drawbarsArr) //Go through each drawbar
    {

//            //Called when key was pressed or key was released etc..
            if(midiEvent.isNoteOn())
            {
                const auto oscillatorId = midiEvent.getNoteNumber(); //Gets note for oscillator from MIDI event
                const auto frequency = midiNoteNumberToFrequency(oscillatorId);
                drawbar.oscillators[oscillatorId].setFrequency(frequency); //Set Oscillator to the frequency of the MIDI note played
                
            }
            if(midiEvent.isNoteOff())
            {
                const auto oscillatorId = midiEvent.getNoteNumber();
                drawbar.oscillators[oscillatorId].stop();
                
            }
            if(midiEvent.isAllNotesOff())
            {
             
                    for(auto& oscillator : drawbar.oscillators)
                    {
                        oscillator.stop();
                    }
        
            }
    }
    
}

float TonewheelOrganSynthAudioProcessor::midiNoteNumberToFrequency(int midiNoteNumber)
{
    constexpr auto A4_FREQUENCY = 440.f; //Fundamental frequency
    constexpr auto A4_NOTE_NUMBER = 69.f; //
    constexpr auto SEMITONES_IN_AN_OCTAVE = 12.f;
    
    return A4_FREQUENCY * std::powf(2.f, (midiNoteNumber - A4_NOTE_NUMBER) / SEMITONES_IN_AN_OCTAVE);
    //Fundamental frequency shifted relative to its position
    //Subtract the A4 note number from the midi note number to get the absolute difference
   // 2^(difference in semitones)
}

void TonewheelOrganSynthAudioProcessor::render(juce::AudioBuffer<float> &buffer, int startSample, int endSample)
{
    auto * firstChannel = buffer.getWritePointer(0);
    for(auto& drawbar : drawbarsArr) //Go through each drawbar
    {
        for(auto& oscillator : drawbar.oscillators) //Each oscillator in the drawbar
        {
            if(oscillator.isPlaying())
            {
                for(auto sample = startSample; sample < endSample; sample++)
                {
                    firstChannel[sample] += oscillator.getSample() * drawbar.volumeLevel; //Add each sample from the oscillator to channel buffer
                }
            }
        }
    }
    for(auto channel = 1; channel < buffer.getNumChannels(); channel++)
    {
        std::copy(firstChannel + startSample, firstChannel + endSample, buffer.getWritePointer(channel) + startSample); //Copy first channel to all channels
     
    }
//    reverb.processMono(firstChannel, buffer.getNumSamples());
////    envelope.applyEnvelopeToBuffer (buffer, 0, buffer.getNumSamples());

}
