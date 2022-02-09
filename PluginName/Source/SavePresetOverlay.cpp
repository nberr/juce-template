/*
  ==============================================================================

    SavePresetOverlay.cpp
    Created: 19 Jan 2022 12:22:29pm
    Author:  Nicholas Berriochoa

  ==============================================================================
*/

#include "SavePresetOverlay.h"

#include "PresetPanel.h"

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
    addAndMakeVisible(notesInput);
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
    notesInput.setBounds(200, 200, 200, 50);
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
        juce::String notes = notesInput.getText();
        
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
        
        // check if notes contain bad text
        if (notes.contains("bad text")) {
            return;
        }
        
        // save the preset to a file
        presetManager->saveAsPreset(name, notes);
        
        // add the preset to the user PresetViewItem tree
        // display automatically updates when a new item is added
        presetManager->addUserPreset(new PresetViewItem(name, notes, false));
        
        // reset the form for next time
        presetNameInput.setText("");
        notesInput.setText("");
        setVisible(false);
        
        juce::Component *overlay = getParentComponent()->findChildWithID("PresetDisplayOverlayID");
        if (overlay != nullptr) {
            overlay->setVisible(true);
        }
        
        auto presetPanel = (PresetPanel *)getParentComponent()->findChildWithID("PresetPanelID");
        presetPanel->setPresetMenu(name);
    }
}
