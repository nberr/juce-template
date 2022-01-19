/*
  ==============================================================================

    SavePresetOverlay.cpp
    Created: 19 Jan 2022 12:22:29pm
    Author:  Nicholas Berriochoa

  ==============================================================================
*/

#include "SavePresetOverlay.h"

//==============================================================================
SavePresetOverlay::SavePresetOverlay(PluginNameAudioProcessor* inProcessor, ContextMenu* inContextMenu)
:   PanelBase(inProcessor, inContextMenu)
{
    setName("SavePresetOverlay");
    setComponentID("SavePresetOverlayID");
    
    presetManager = mProcessor->getPresetManager();
    
    isOverlay = true;
    
    // initialize each button and add them to the scene
    for (juce::TextButton* button : buttons) {
        button->setTriggeredOnMouseDown(true);
        button->addListener(this);
        addAndMakeVisible(button);
    }
}

SavePresetOverlay::~SavePresetOverlay()
{
    
}

//==============================================================================
void SavePresetOverlay::resized()
{
    close.setBounds(0, 0, 40, 40);
}

//==============================================================================
void SavePresetOverlay::buttonClicked(juce::Button* b)
{
    if (b == &close) {
        setVisible(false);
        
        juce::Component* overlay = getParentComponent()->findChildWithID("DisplayPresetsOverlayID");
        if (overlay != nullptr) {
            overlay->setVisible(true);
        }
        
    }
}
