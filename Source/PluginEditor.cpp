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
        drawbarSlider.setRange(1,8,1);
        
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
    g.drawFittedText ("16'", (centeredPos),getHeight() - 50,centeredPos,50, juce::Justification::topLeft, 1);
    g.drawFittedText ("5 1/3'", (10 + centeredPos) * 2,getHeight() - 50,centeredPos,50, juce::Justification::topLeft, 1);
    g.drawFittedText ("8'", (20 + centeredPos) * 3,getHeight() - 50,centeredPos,50, juce::Justification::topLeft, 1);
    g.drawFittedText ("4'", (20 + centeredPos) * 4,getHeight() - 50,centeredPos,50, juce::Justification::topLeft, 1);
    g.drawFittedText ("2 2/3'", (20 + centeredPos) * 5,getHeight() - 50,centeredPos,50, juce::Justification::topLeft, 1);
    g.drawFittedText ("2'", (20 + centeredPos) * 6,getHeight() - 50,centeredPos,50, juce::Justification::topLeft, 1);
    g.drawFittedText ("1 3/5'", (20 + centeredPos) * 7,getHeight() - 50,centeredPos,50, juce::Justification::topLeft, 1);
    g.drawFittedText ("1 1/3'", (20 + centeredPos) * 8,getHeight() - 50,centeredPos,50, juce::Justification::topLeft, 1);
    g.drawFittedText ("1'", (20 + centeredPos) * 9,getHeight() - 50,centeredPos,50, juce::Justification::topLeft, 1);
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
