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
    for(auto& drawbarSlider : DrawbarSliders)
    {
        addAndMakeVisible(drawbarSlider); // Make all drawbar sliders visible
        drawbarSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBarVertical); //Make all drawbars vertical sliders
        drawbarSlider.setRange(0,8,1);
        
    }
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
    g.drawFittedText ("16'", DrawbarSliders[0].getX() + getWidth()/30,getHeight() - 50,centeredPos,50, juce::Justification::topLeft, 1);
    g.drawFittedText ("5 1/3'", DrawbarSliders[1].getX() + getWidth()/50,getHeight() - 50,centeredPos,50, juce::Justification::topLeft, 1);
    g.drawFittedText ("8'", DrawbarSliders[2].getX() + getWidth()/30,getHeight() - 50,centeredPos,50, juce::Justification::topLeft, 1);
    g.drawFittedText ("4'", DrawbarSliders[3].getX() + getWidth()/30,getHeight() - 50,centeredPos,50, juce::Justification::topLeft, 1);
    g.drawFittedText ("2 2/3'", DrawbarSliders[4].getX() + getWidth()/50,getHeight() - 50,centeredPos,50, juce::Justification::topLeft, 1);
    g.drawFittedText ("2'", DrawbarSliders[5].getX() + getWidth()/30,getHeight() - 50,centeredPos,50, juce::Justification::topLeft, 1);
    g.drawFittedText ("1 3/5'", DrawbarSliders[6].getX() + getWidth()/50,getHeight() - 50,centeredPos,50, juce::Justification::topLeft, 1);
    g.drawFittedText ("1 1/3'", DrawbarSliders[7].getX() + getWidth()/50,getHeight() - 50,centeredPos,50, juce::Justification::topLeft, 1);
    g.drawFittedText ("1'", DrawbarSliders[8].getX() + getWidth()/30,getHeight() - 50,centeredPos,50, juce::Justification::topLeft, 1);
}

void TonewheelAudioProcessorEditor::resized()
{
    const int border = 10;
    const int drawbarWidth = getWidth()/10;
    const int drawbarHeight = getHeight() * 0.75 - getHeight()/10;
    for(auto i = 0; i < juce::numElementsInArray(DrawbarSliders); i++)
    {
        DrawbarSliders[i].setBounds((border + drawbarWidth) * i, getHeight() * 0.25, drawbarWidth, drawbarHeight); // Position all sliders
//        DrawbarSliders[i].setBoundsRelative(0.1f * i + 1, 0.1f * i + 1, 0.1f, 0.1f); // Position all sliders
    }
}
