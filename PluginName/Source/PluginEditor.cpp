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
    : AudioProcessorEditor (&p), audioProcessor (p), mContextMenu(&(PluginNameParameters::mGUIScale)),
    mMenuPanel(&audioProcessor, &mContextMenu),
    mPresetPanel(&audioProcessor, &mContextMenu),
    mPresetOverlay(&audioProcessor, &mContextMenu),
    mMainPanel(&audioProcessor, &mContextMenu),
    mSidePanel(&audioProcessor, &mContextMenu)
{
    setSize (PluginNameGUI::width, PluginNameGUI::height);
    
    // This template allows two ways to display a UI
    // 1 - pure JUCE; see UI folder for panel hierarchy
    // 2 - react-juce; see jsui/src/index.js
    
    // JUCE UI implementation
    setSize(PluginNameGUI::width, PluginNameGUI::height);
    setName("PluginEditor");
    setComponentID("PluginEditorID");
    setResizable(false, false);
        
    addAndMakeVisible(mMenuPanel);
    addAndMakeVisible(mPresetPanel);
    //addChildComponent(mPresetOverlay); // add to scene but don't make visible
    addAndMakeVisible(&mMainPanel);
    addAndMakeVisible(mSidePanel); // add to scene but don't make visible
    
    // React UI implementation
    // Use this code if your js is stored locally
    //juce::File bundle = juce::File("/Users/nberr/Developer/plugin-dev/plugin-template/PluginName/Source/jsui/build/js/main.js");
    
    // Use this code if your js is stored on a server
    // TODO: implement pulling js from a server
    
    // js needs to be evaluated and added to the scene to be visible
    //appRoot.evaluate(bundle);
    //addAndMakeVisible(appRoot);
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
    // JUCE UI implementation
    float scale = PluginNameParameters::mGUIScale;
    int width = PluginNameGUI::width;
    if (PluginNameParameters::mShowSidePanel) {
        width += SidePanelGUI::width;
    }
        
    setSize(width * scale, PluginNameGUI::height * scale);
        
    mMenuPanel.setBounds(0, 0, MenuPanelGUI::width * scale, MenuPanelGUI::height * scale);
    mPresetPanel.setBounds(mMenuPanel.getRight(), 0, PresetPanelGUI::width * scale, PresetPanelGUI::height * scale);
    mMainPanel.setBounds(mMenuPanel.getRight(), mPresetPanel.getBottom(), MainPanelGUI::width * scale, MainPanelGUI::height * scale);
    mSidePanel.setBounds(mMainPanel.getRight(), 0, SidePanelGUI::width * scale, SidePanelGUI::height * scale);

    // React UI implementation
    //appRoot.setBounds(getLocalBounds());
}
