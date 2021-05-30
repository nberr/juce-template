/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

#include "InterfaceDefines.h"

//==============================================================================
PluginNameAudioProcessorEditor::PluginNameAudioProcessorEditor (PluginNameAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    
    setSize(MAIN_PANEL_WIDTH, MAIN_PANEL_HEIGHT);
    setResizable(false, false);
    
    mMainPanel = std::make_unique<MainPanel>(&audioProcessor);
    mMainPanel->setTopLeftPosition(0, 0);
    addAndMakeVisible(*mMainPanel);
    
    
}

PluginNameAudioProcessorEditor::~PluginNameAudioProcessorEditor()
{
}

//==============================================================================
void PluginNameAudioProcessorEditor::paint (juce::Graphics& g)
{
    
}

void PluginNameAudioProcessorEditor::resized()
{
    
}
