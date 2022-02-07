/*
  ==============================================================================

    SavePresetOverlay.cpp
    Created: 19 Jan 2022 12:22:29pm
    Author:  Nicholas Berriochoa

  ==============================================================================
*/

#include "SavePresetOverlay.h"

//==============================================================================
SavePresetOverlay::SavePresetOverlay(PluginNameAudioProcessor* processor, ContextMenu* contextMenu)
:   OverlayBase(processor, contextMenu)
{
    setName("SavePresetOverlay");
    setComponentID("SavePresetOverlayID");
    
    presetManager = processor->getPresetManager();
    
    // initialize each button and add them to the scene
    for (juce::Button* button : buttons) {
        button->setTriggeredOnMouseDown(true);
        button->addListener(this);
        addAndMakeVisible(button);
    }
    
    addAndMakeVisible(presetNameInput);
}

SavePresetOverlay::~SavePresetOverlay()
{
    
}

//==============================================================================
void SavePresetOverlay::resized()
{
    close.setBounds(0, 0, 40, 40);
    save.setBounds (40, 40, 40, 40);
    presetNameInput.setBounds(100, 100, 200, 50);
}

//==============================================================================
void SavePresetOverlay::buttonClicked(juce::Button* b)
{
    if (b == &close) {
        setVisible(false);
        presetNameRequired.setVisible(false);
        
        juce::Component* overlay = getParentComponent()->findChildWithID("PresetDisplayOverlayID");
        if (overlay != nullptr) {
            overlay->setVisible(true);
        }
        
    }
    else if (b == &save) {
        juce::String name = "";
        
        if (presetNameInput.isEmpty()) {
            // preset name is required
            presetNameRequired.setVisible(true);
            return;
        }
        else {
            name = presetNameInput.getText();
        }
        
        // check if the name is valid
        if (name.contains("bad text")) {
            return;
        }
        
        // TODO: sanitize notes text
        presetManager->saveAsPreset(name, notes.getText());
        
        // TODO: reload values in PresetDisplayOverlay
    }
}
