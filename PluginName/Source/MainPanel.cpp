/*
  ==============================================================================

    MainPanel.cpp
    Created: 25 Nov 2021 8:56:29am
    Author:  Nicholas Berriochoa

  ==============================================================================
*/

#include "MainPanel.h"

#if JUCE_WINDOWS
    #define DIR_SEP "\\"
#elseif JUCE_MAC
    #define DIR_SEP "/"
#else
    #define DIR_SEP "/"
#endif

MainPanel::MainPanel(PluginNameAudioProcessor* inProcessor, ContextMenu* inContextMenu)
:   PanelBase(inProcessor, inContextMenu),
    appHarness(appRoot),
    unlockForm(marketplaceStatus),
    mPresetPanel(inProcessor, inContextMenu),
    mPresetOverlay(inProcessor, inContextMenu)
{
    setSize(MainPanelGUI::width * *mContextMenu->mGUIScale, MainPanelGUI::height * *mContextMenu->mGUIScale);
    setName("MainPanel");
    setComponentID("MainPanelID");
    
    // TODO: change url
    //juce::String path = juce::File::getSpecialLocation(juce::File::userMusicDirectory).getFullPathName() + DIR_SEP + JucePlugin_Manufacturer + DIR_SEP + JucePlugin_Name + DIR_SEP;
    juce::String path = "/Users/noidexp/Documents/GitHub/plugin-template/PluginName/Source/jsui/build/js/main.js";
    
    //juce::String url = "https://noidexp.com/" + juce::String(JucePlugin_Name) + "/jsui/" + JucePlugin_VersionString + "/main.js";
    //juce::String url = "debug";
    //juce::MemoryBlock jsData;
    //juce::URL mainjs = juce::URL(url);
    juce::File bundle = juce::File(path);
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
    
    //addAndMakeVisible(&mPresetPanel);
    //addChildComponent(&mPresetOverlay); // add to scene but don't make visible
}

MainPanel::~MainPanel()
{
    
}


void MainPanel::resized()
{
    float scale = *mContextMenu->mGUIScale;
    
    mPresetPanel.setBounds(0, 0, PresetPanelGUI::width * scale, PresetPanelGUI::height * scale);
    mPresetOverlay.setBounds(0, PresetPanelGUI::height * scale, PresetOverlayGUI::width * scale, PresetOverlayGUI::height * scale);
    
    appRoot.setBounds(0, 0, MainPanelGUI::width * scale, MainPanelGUI::height * scale);
}

void MainPanel::timerCallback()
{
    if (! isUnlocked && marketplaceStatus.isUnlocked())
    {
        isUnlocked = true;
        unlockApp();
    }
}

void MainPanel::showForm()
{
    unlockForm.setVisible (true);
}

void MainPanel::unlockApp()
{
    secretButton.setEnabled (true);
    unlockButton.setEnabled (false);

    unlockLabel.setText ("Status: Unlocked", juce::dontSendNotification);
    unlockLabel.setColour (juce::Label::textColourId, juce::Colours::green);
}

void MainPanel::checkFeature()
{
    if (marketplaceStatus.isUnlocked())
        DBG ("App unlocked!");
    else
        DBG ("Beware of hackers!");
}
