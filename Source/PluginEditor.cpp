/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
TonewheelOrganSynthAudioProcessorEditor::TonewheelOrganSynthAudioProcessorEditor (TonewheelOrganSynthAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (800, 600);
    for(auto i = 0; i < juce::numElementsInArray(drawbarSliders); i++)
    {
        addAndMakeVisible(drawbarSliders[i]); // Make all drawbar sliders visible
        drawbarSliders[i].setSliderStyle(juce::Slider::SliderStyle::LinearBarVertical); //Linear bar style
        drawbarSliders[i].setRange(0,8,1); // Volume between 0 and 8
    }
    //Make slider attachments for drawbars
    drawbarOneGainAttachment = std::make_unique< juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "DRAWBARGAIN1", drawbarSliders[0]);
     drawbarTwoGainAttachment = std::make_unique< juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "DRAWBARGAIN2", drawbarSliders[1]);
    drawbarThreeGainAttachment = std::make_unique< juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "DRAWBARGAIN3", drawbarSliders[2]);
    drawbarFourGainAttachment = std::make_unique< juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "DRAWBARGAIN4", drawbarSliders[3]);
    drawbarFiveGainAttachment = std::make_unique< juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "DRAWBARGAIN5", drawbarSliders[4]);
    drawbarSixGainAttachment = std::make_unique< juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "DRAWBARGAIN6", drawbarSliders[5]);
    drawbarSevenGainAttachment = std::make_unique< juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "DRAWBARGAIN7", drawbarSliders[6]);
    drawbarEightGainAttachment = std::make_unique< juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "DRAWBARGAIN8", drawbarSliders[7]);
    drawbarNineGainAttachment = std::make_unique< juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "DRAWBARGAIN9", drawbarSliders[8]);
    
}

TonewheelOrganSynthAudioProcessorEditor::~TonewheelOrganSynthAudioProcessorEditor()
{
}

//==============================================================================
void TonewheelOrganSynthAudioProcessorEditor::paint (juce::Graphics& g)
{
   // g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    
    auto BGFile = juce::File("/Users/lilianljungkvist/Projects/codingProjects/Uni/Yr3/AAVP/TonewheelOrgan/woodBG.jpg");
    juce::Image background = juce::ImageCache::getFromFile(BGFile);
      g.drawImageAt (background, 0, 0);
    g.setColour (juce::Colours::whitesmoke);
    g.fillRoundedRectangle(5, 5, getWidth() * 3/4, getWidth()/9, 14);
    g.setColour (juce::Colours::black);
    auto titleFont = juce::Font("Didot", 64.0f, 1);
    g.setFont (titleFont);
    g.drawFittedText ("Tonewheel Organ Synth", 10,10,getWidth(),getWidth()/8, juce::Justification::topLeft, 1);
    g.setColour (juce::Colours::whitesmoke);
    g.setFont (20.0f);
    //Draw the lengths of pipes the drawbars symbolise
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

void TonewheelOrganSynthAudioProcessorEditor::resized()
{
    //Draws 9 drawbars equally spaced across the window
    const int border = 10;
    const int drawbarWidth = getWidth()/10;
    const int drawbarHeight = getHeight() * 0.75 - getHeight()/10;
    for(auto i = 0; i < juce::numElementsInArray(drawbarSliders); i++)
    {
        drawbarSliders[i].setBounds((border + drawbarWidth) * i, getHeight() * 0.25, drawbarWidth, drawbarHeight);
  
    }
    

}
