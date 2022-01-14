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
    : AudioProcessorEditor (&p), audioProcessor (p), mContextMenu(&(PluginNameInternalParameters::GUIScale)),
    mMenuPanel(&audioProcessor, &mContextMenu),
    mPresetPanel(&audioProcessor, &mContextMenu),
    mPresetOverlay(&audioProcessor, &mContextMenu),
    mMainPanel(&audioProcessor, &mContextMenu),
    mSidePanel(&audioProcessor, &mContextMenu),
    appHarness(appRoot),
    unlockForm(marketplaceStatus)
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
    
    mPresetOverlay.setAlwaysOnTop(true);
        
    addAndMakeVisible(mMenuPanel);
    addAndMakeVisible(mPresetPanel);
    addChildComponent(mPresetOverlay); // add to scene but don't make visible
    addAndMakeVisible(mMainPanel);
    addAndMakeVisible(mSidePanel); // add to scene but don't make visible
    
    // React UI implementation
    // Use this code if your js is stored locally
    //juce::File bundle = juce::File("/Users/nberr/Developer/plugin-dev/plugin-template/PluginName/Source/jsui/build/js/main.js");
    
    // Use this code if your js is stored on a server
    // js needs to be evaluated and added to the scene to be visible
    // change url to wherever the .js file is on your server
    //juce::String path = juce::File::getSpecialLocation(juce::File::userMusicDirectory).getFullPathName() + DIR_SEP + JucePlugin_Manufacturer + DIR_SEP + JucePlugin_Name + DIR_SEP;
    // juce::String path = "/Users/noidexp/Documents/GitHub/plugin-template/PluginName/Source/jsui/build/js/main.js";
    
    //juce::String url = "https://nberr.io/" + juce::String(JucePlugin_Name) + "/jsui/" + JucePlugin_VersionString + "/main.js";
    //juce::String url = "debug";
    //juce::MemoryBlock jsData;
    //juce::URL mainjs = juce::URL(url);
    // juce::File bundle = juce::File(path);
    //bundle.createDirectory();
    //bundle = juce::File(path);
    
    /*
    if (bundle.exists()) {
        // local file exists
        // check for update
        if (mainjs.readEntireBinaryStream(jsData)) {
            juce::File serverBundle = juce::File("~/Desktop/server.js");
            serverBundle.replaceWithData(jsData.getData(), jsData.getSize());
            
            if (bundle.hasIdenticalContentTo(serverBundle)) {
                // files are the same
                serverBundle.deleteFile();
            }
            else {
                // files are different
                bundle.replaceWithData(jsData.getData(), jsData.getSize());
                serverBundle.deleteFile();
            }
        }
    }
    else {
        // local file doesn't exist yet
        // try to download js from server, else use the default
        if (mainjs.readEntireBinaryStream(jsData)) {
            bundle.replaceWithData(jsData.getData(), jsData.getSize());
        }
        else {
            bundle.replaceWithData(BinaryData::main_js, BinaryData::main_jsSize);
        }
    }*/
    
    //appRoot.evaluate(bundle);
    //appHarness.watch(bundle);
    //addAndMakeVisible(appRoot);
    //appHarness.start();
    
    unlockLabel.setSize(50, 50);
    unlockLabel.setTopLeftPosition(0, 0);
    unlockLabel.setFont (juce::Font (15.0f, juce::Font::bold));
    unlockLabel.setColour (juce::Label::textColourId, juce::Colours::red);
    //addAndMakeVisible (unlockLabel);

    unlockButton.setSize(100, 100);
    unlockButton.setTopLeftPosition(50, 50);
    unlockButton.onClick = [this] {
        showForm();
    };
    //addAndMakeVisible (unlockButton);

    secretButton.setEnabled (false);
    secretButton.onClick = [this] { checkFeature(); };
    //addAndMakeVisible (secretButton);

    unlockForm.setSize(MainPanelGUI::width, MainPanelGUI::height);
    unlockForm.setTopLeftPosition(0, 0);
    //addChildComponent (unlockForm);
    
    startTimer(100);
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
    float scale = PluginNameInternalParameters::GUIScale;
    int width = PluginNameGUI::width;
    if (PluginNameInternalParameters::showSidePanel) {
        width += SidePanelGUI::width;
    }
        
    setSize(width * scale, PluginNameGUI::height * scale);
        
    mMenuPanel.setBounds(0, 0,
                         MenuPanelGUI::width * scale,
                         MenuPanelGUI::height * scale);
    mPresetPanel.setBounds(mMenuPanel.getRight(), 0,
                           PresetPanelGUI::width * scale,
                           PresetPanelGUI::height * scale);
    mMainPanel.setBounds(mMenuPanel.getRight(), mPresetPanel.getBottom(),
                         MainPanelGUI::width * scale,
                         MainPanelGUI::height * scale);
    mSidePanel.setBounds(mMainPanel.getRight(), 0,
                         SidePanelGUI::width * scale,
                         SidePanelGUI::height * scale);
    
    mPresetOverlay.setBounds(mMenuPanel.getRight(), mPresetPanel.getBottom(),
                             MainPanelGUI::width * scale,
                             MainPanelGUI::height * scale);

    // React UI implementation
    //appRoot.setBounds(getLocalBounds());
}

//==============================================================================
void PluginNameAudioProcessorEditor::timerCallback()
{
    // need this to resize the plugin form the context menu
    resized();
    
    if (! isUnlocked && marketplaceStatus.isUnlocked())
    {
        isUnlocked = true;
        unlockApp();
    }
}

void PluginNameAudioProcessorEditor::showForm()
{
    unlockForm.setVisible (true);
}

void PluginNameAudioProcessorEditor::unlockApp()
{
    secretButton.setEnabled (true);
    unlockButton.setEnabled (false);

    unlockLabel.setText ("Status: Unlocked", juce::dontSendNotification);
    unlockLabel.setColour (juce::Label::textColourId, juce::Colours::green);
}

void PluginNameAudioProcessorEditor::checkFeature()
{
    if (marketplaceStatus.isUnlocked())
        DBG ("App unlocked!");
    else
        DBG ("Beware of hackers!");
}
