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
:   AudioProcessorEditor (&p),
    audioProcessor (p),
    mContextMenu(&(audioProcessor.internalParameters.mGUIScale)),
    mMainPanel(&audioProcessor, &mContextMenu)
{
    mGUIScale = &(audioProcessor.internalParameters.mGUIScale);
    setSize(Panel_Size::main_panel_width, Panel_Size::main_panel_height);
    setName("PluginEditor");
    setResizable(false, false);
    
    addAndMakeVisible(&mMainPanel);
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
    setSize(Panel_Size::main_panel_width * *mGUIScale, Panel_Size::main_panel_height * *mGUIScale);
    mMainPanel.setBounds(0, 0, Panel_Size::main_panel_width * *mGUIScale, Panel_Size::main_panel_height * *mGUIScale);
}

