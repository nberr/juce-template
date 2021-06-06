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
    : AudioProcessorEditor (&p), audioProcessor (p), small("small"), medium("medium"), large("large")
{
    mGUIScale = &(audioProcessor.internalParameters.mGUIScale);
    
    setSize(MAIN_PANEL_WIDTH * *mGUIScale, MAIN_PANEL_HEIGHT * *mGUIScale);
    setResizable(false, false);
    
    mMainPanel = std::make_unique<MainPanel>(&audioProcessor);
    mMainPanel->setTopLeftPosition(0, 0);
    //addAndMakeVisible(*mMainPanel);
    
    small.setBounds(0, 0, 50, 50);
    medium.setBounds(50, 0, 50, 50);
    large.setBounds(100, 0, 50, 50);
    
    addAndMakeVisible(small);
    addAndMakeVisible(medium);
    addAndMakeVisible(large);
    
    small.onClick = [this] {
        *mGUIScale = SMALL;
        resized();
    };
    
    medium.onClick = [this] {
        *mGUIScale = MEDIUM;
        resized();
    };
    
    large.onClick = [this] {
        *mGUIScale = LARGE;
        resized();
    };
    
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
