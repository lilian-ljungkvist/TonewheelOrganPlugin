/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
TonewheelAudioProcessor::TonewheelAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
}

TonewheelAudioProcessor::~TonewheelAudioProcessor()
{
}

//==============================================================================
const juce::String TonewheelAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool TonewheelAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool TonewheelAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool TonewheelAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double TonewheelAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int TonewheelAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int TonewheelAudioProcessor::getCurrentProgram()
{
    return 0;
}

void TonewheelAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String TonewheelAudioProcessor::getProgramName (int index)
{
    return {};
}

void TonewheelAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void TonewheelAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    auto drawbarVolumes = getDrawBarSettings(apvts);
    organ.prepareToPlay(sampleRate);
}

void TonewheelAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool TonewheelAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void TonewheelAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    auto drawbarVolumes = getDrawBarSettings(apvts);
    juce::ScopedNoDenormals noDenormals;
    organ.processBlock(buffer, midiMessages);
    
   
//    oscillator * drawBarVolumes.volume1
    
    
}

//==============================================================================
bool TonewheelAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* TonewheelAudioProcessor::createEditor()
{
    return new TonewheelAudioProcessorEditor (*this);
}

//==============================================================================
void TonewheelAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void TonewheelAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new TonewheelAudioProcessor();
}

juce::AudioProcessorValueTreeState::ParameterLayout TonewheelAudioProcessor::paramCreate()
{
    juce::AudioProcessorValueTreeState::ParameterLayout params;
   
    params.add(std::make_unique<juce::AudioParameterFloat>("DRAWBARVGAIN1", "Drawbar 1 Gain", juce::NormalisableRange<float>(0.0f, 12.0f, 1.0f, 1.0f), 0.0f));
    params.add(std::make_unique<juce::AudioParameterFloat>("DRAWBARVGAIN2", "Drawbar 2 Gain", juce::NormalisableRange<float>(0.0f, 12.0f, 1.0f, 1.0f), 0.0f));
    params.add(std::make_unique<juce::AudioParameterFloat>("DRAWBARVGAIN3", "Drawbar 3 Gain", juce::NormalisableRange<float>(0.0f, 12.0f, 1.0f, 1.0f), 0.0f));
    params.add(std::make_unique<juce::AudioParameterFloat>("DRAWBARVGAIN4", "Drawbar 4 Gain", juce::NormalisableRange<float>(0.0f, 12.0f, 1.0f, 1.0f), 0.0f));
    params.add(std::make_unique<juce::AudioParameterFloat>("DRAWBARVGAIN5", "Drawbar 5 Gain", juce::NormalisableRange<float>(0.0f, 12.0f, 1.0f, 1.0f), 0.0f));
    params.add(std::make_unique<juce::AudioParameterFloat>("DRAWBARVGAIN6", "Drawbar 6 Gain", juce::NormalisableRange<float>(0.0f, 12.0f, 1.0f, 1.0f), 0.0f));
    params.add(std::make_unique<juce::AudioParameterFloat>("DRAWBARVGAIN7", "Drawbar 7 Gain", juce::NormalisableRange<float>(0.0f, 12.0f, 1.0f, 1.0f), 0.0f));
    params.add(std::make_unique<juce::AudioParameterFloat>("DRAWBARVGAIN8", "Drawbar 8 Gain", juce::NormalisableRange<float>(0.0f, 12.0f, 1.0f, 1.0f), 0.0f));
    params.add(std::make_unique<juce::AudioParameterFloat>("DRAWBARVGAIN9", "Drawbar 9 Gain", juce::NormalisableRange<float>(0.0f, 12.0f, 1.0f, 1.0f), 0.0f));
    
    return params;
    
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
    
    return settings;
}
