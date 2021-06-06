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
    mGUIScale = &(audioProcessor.internalParameters.mGUIScale);
    
    setSize(MAIN_PANEL_WIDTH * *mGUIScale, MAIN_PANEL_HEIGHT * *mGUIScale);
    setResizable(false, false);
    
    mMainPanel = std::make_unique<MainPanel>(&audioProcessor, &mContextMenu);
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
    setSize(MAIN_PANEL_WIDTH* *mGUIScale, MAIN_PANEL_HEIGHT* *mGUIScale);
}
