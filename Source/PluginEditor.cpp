/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Template_AudioProcessorEditor::Template_AudioProcessorEditor (Template_AudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    setSize (MAIN_PANEL_WIDTH, MAIN_PANEL_HEIGHT);
    
    mMainPanel = std::make_unique<MainPanel>(&audioProcessor);
    mMainPanel->setTopLeftPosition(0, 0);
    addAndMakeVisible(*mMainPanel);
}

Template_AudioProcessorEditor::~Template_AudioProcessorEditor()
{
    
}

//==============================================================================
void Template_AudioProcessorEditor::paint (juce::Graphics& g)
{
    
}

void Template_AudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
