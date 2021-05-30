/*
  ==============================================================================

    MainPanel.cpp
    Created: 12 Apr 2021 5:03:39pm
    Author:  Nicholas Berriochoa

  ==============================================================================
*/

#include "MainPanel.h"

MainPanel::MainPanel(PluginNameAudioProcessor *inProcessor)
:   PanelBase(inProcessor),
    unlockForm(marketplaceStatus)
{
    setSize(MAIN_PANEL_WIDTH, MAIN_PANEL_HEIGHT);
    setInterceptsMouseClicks(true, true);
    
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

    unlockForm.setSize(MAIN_PANEL_WIDTH, MAIN_PANEL_HEIGHT);
    unlockForm.setTopLeftPosition(0, 0);
    addChildComponent (unlockForm);
    
    startTimer(100);
    
    mPresetPanel = std::make_unique<PresetPanel>(inProcessor);
    mPresetPanel->setTopLeftPosition(0, 0);
    addAndMakeVisible(*mPresetPanel);
}

MainPanel::~MainPanel()
{
    
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

void MainPanel::mouseDown(const juce::MouseEvent& event)
{
    bool rightClick = juce::ModifierKeys::getCurrentModifiers().isPopupMenu();
    
    
    if (rightClick) {
        juce::PopupMenu menu, preferences, sizes;
        
        sizes.addItem("Small", [](){});
        sizes.addItem("Medium", [](){});
        sizes.addItem("Large", [](){});
        
        preferences.addItem("Dark Mode", [](){});
        preferences.addSubMenu("Size", sizes);
                
        menu.addSubMenu("Preferences", preferences);
        menu.addSeparator();
        menu.addItem("PluginName version 1.0", [](){});

        const int result = menu.show();
        
        if (result == 0) {
            setSize(45, 45);
        }
        else {
            
        }
    }
}
