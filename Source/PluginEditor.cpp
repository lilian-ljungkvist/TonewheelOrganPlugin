/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
TonewheelAudioProcessorEditor::TonewheelAudioProcessorEditor (TonewheelAudioProcessor& p)
: AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (800, 600);
    
    for(auto i = 0; i < juce::numElementsInArray(drawbarSliders); i++)
    {
        addAndMakeVisible(drawbarSliders[i]); // Make all drawbar sliders visible
        drawbarSliders[i].setSliderStyle(juce::Slider::SliderStyle::LinearBarVertical);
        //Make all drawbars vertical sliders
//        drawbarSliders[i].setRange(0,8,1);
//        auto thisDrawbar = organ.drawbars[i];
//        auto thisSlider = &drawbarSliders[i];
//        int volLevel = thisSlider->getValue();
//        thisSlider->onValueChange() = [thisSlider, &volLevel] () -> int { return volLevel = thisSlider->getValue(); };

//        organ.drawbars[i].setVolumeLevel(volLevel);

    }
    
    volume1 = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "DRAWBARVGAIN1", drawbarSliders[0]);
    volume2 = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "DRAWBARVGAIN2", drawbarSliders[1]);
    volume3 = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "DRAWBARVGAIN3", drawbarSliders[2]);
    volume4 = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "DRAWBARVGAIN4", drawbarSliders[3]);
    volume5 = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "DRAWBARVGAIN5", drawbarSliders[4]);
    volume6 = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "DRAWBARVGAIN6", drawbarSliders[5]);
    volume7 = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "DRAWBARVGAIN7", drawbarSliders[6]);
    volume8 = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "DRAWBARVGAIN8", drawbarSliders[7]);
    volume9 = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "DRAWBARVGAIN9", drawbarSliders[8]);
    
    

}

TonewheelAudioProcessorEditor::~TonewheelAudioProcessorEditor()
{
}

//==============================================================================
void TonewheelAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::goldenrod);
    g.setFont (48.0f);
    g.drawFittedText ("Tonewheel Organ Synth", 10,10,getWidth(),getWidth()/8, juce::Justification::topLeft, 1);
    g.setColour (juce::Colours::whitesmoke);
    g.setFont (20.0f);
    
    int centeredPos = getWidth()/20;
    g.drawFittedText ("16'", drawbarSliders[0].getX() + getWidth()/30,getHeight() - 50,centeredPos,50, juce::Justification::topLeft, 1);
    g.drawFittedText ("5 1/3'", drawbarSliders[1].getX() + getWidth()/50,getHeight() - 50,centeredPos,50, juce::Justification::topLeft, 1);
    g.drawFittedText ("8'", drawbarSliders[2].getX() + getWidth()/30,getHeight() - 50,centeredPos,50, juce::Justification::topLeft, 1);
    g.drawFittedText ("4'", drawbarSliders[3].getX() + getWidth()/30,getHeight() - 50,centeredPos,50, juce::Justification::topLeft, 1);
    g.drawFittedText ("2 2/3'", drawbarSliders[4].getX() + getWidth()/50,getHeight() - 50,centeredPos,50, juce::Justification::topLeft, 1);
    g.drawFittedText ("2'", drawbarSliders[5].getX() + getWidth()/30,getHeight() - 50,centeredPos,50, juce::Justification::topLeft, 1);
    g.drawFittedText ("1 3/5'", drawbarSliders[6].getX() + getWidth()/50,getHeight() - 50,centeredPos,50, juce::Justification::topLeft, 1);
    g.drawFittedText ("1 1/3'", drawbarSliders[7].getX() + getWidth()/50,getHeight() - 50,centeredPos,50, juce::Justification::topLeft, 1);
    g.drawFittedText ("1'", drawbarSliders[8].getX() + getWidth()/30,getHeight() - 50,centeredPos,50, juce::Justification::topLeft, 1);
    
 
}

void TonewheelAudioProcessorEditor::resized()
{
    const int border = 10;
    const int drawbarWidth = getWidth()/10;
    const int drawbarHeight = getHeight() * 0.75 - getHeight()/10;
    for(auto i = 0; i < juce::numElementsInArray(drawbarSliders); i++)
    {
        drawbarSliders[i].setBounds((border + drawbarWidth) * i, getHeight() * 0.25, drawbarWidth, drawbarHeight);
  
    }
    
}


