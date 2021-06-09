/*
  ==============================================================================

    MainPanel.cpp
    Created: 12 Apr 2021 5:03:39pm
    Author:  Nicholas Berriochoa

  ==============================================================================
*/

#include "MainPanel.h"

MainPanel::MainPanel(PluginNameAudioProcessor* inProcessor, ContextMenu* inContextMenu)
:   PanelBase(inProcessor, inContextMenu),
    unlockForm(marketplaceStatus),
    mPresetPanel(inProcessor, inContextMenu),
    mPresetOverlay(inProcessor, inContextMenu)
{
    setSize(MainPanelGUI::panel_width * *mContextMenu->mGUIScale, MainPanelGUI::panel_width * *mContextMenu->mGUIScale);
    setName("MainPanel");
    setComponentID("MainPanelID");
    
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

    unlockForm.setSize(MainPanelGUI::panel_width, MainPanelGUI::panel_height);
    unlockForm.setTopLeftPosition(0, 0);
    //addChildComponent (unlockForm);
    
    startTimer(100);
    
    addAndMakeVisible(&mPresetPanel);
    addChildComponent(&mPresetOverlay); // add to scene but don't make visible
}

MainPanel::~MainPanel()
{
    
}


void MainPanel::resized()
{
    float scale = *mContextMenu->mGUIScale;
    
    mPresetPanel.setBounds(0, 0, PresetPanelGUI::panel_width * scale, PresetPanelGUI::panel_height * scale);
    mPresetOverlay.setBounds(0, PresetPanelGUI::panel_height * scale, PresetOverlayGUI::width * scale, PresetOverlayGUI::height * scale);
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
