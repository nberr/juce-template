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
    setSize(MainPanelGUI::width, MainPanelGUI::height);
    setName("PluginEditor");
    setComponentID("PluginEditorID");
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
    setSize(MainPanelGUI::width * *mGUIScale, MainPanelGUI::height * *mGUIScale);
    mMainPanel.setBounds(0, 0, MainPanelGUI::width * *mGUIScale, MainPanelGUI::height * *mGUIScale);
}

