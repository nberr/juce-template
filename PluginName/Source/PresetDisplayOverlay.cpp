/*
  ==============================================================================

    PresetDisplayOverlay.cpp
    Created: 25 Nov 2021 8:57:24am
    Author:  Nicholas Berriochoa

  ==============================================================================
*/

#include "PresetDisplayOverlay.h"

//==============================================================================
PresetDisplayOverlay::PresetDisplayOverlay(PluginNameAudioProcessor* inProcessor, ContextMenu* inContextMenu)
:   OverlayBase(inProcessor, inContextMenu)
{
    setName("PresetDisplayOverlay");
    setComponentID("PresetDisplayOverlayID");
    
    presetManager = mProcessor->getPresetManager();
    
    rootViewItem = new PresetViewItem("root", "", false, false);
    userPresets = new PresetViewItem("User", "", false, true);
    factoryPresets = new PresetViewItem("Defaults", "", false, true);
    
    // initialize each button and add them to the scene
    for (juce::TextButton* button : buttons) {
        button->setTriggeredOnMouseDown(true);
        button->addListener(this);
        addAndMakeVisible(button);
    }
    
    rootViewItem->setOpen(true);
    
    
    
    rootViewItem->addSubItem(userPresets);
    rootViewItem->addSubItem(factoryPresets);
    
    presetsDisplay.setRootItem(rootViewItem);
    presetsDisplay.setRootItemVisible(false);
    
    addAndMakeVisible(presetsDisplay);
}

PresetDisplayOverlay::~PresetDisplayOverlay()
{
    presetsDisplay.deleteRootItem();
}

//==============================================================================
void PresetDisplayOverlay::resized()
{
    float scale = guiScale.getProperty(juce::Identifier("value"));;
    
    int buffer = 5 * scale;
    float width = PresetPanelGUI::A_B_Copy_width * scale,
          height = PresetPanelGUI::A_B_Copy_height * scale;
    
    addNewPreset.setBounds(buffer,
                            buffer,
                            width,
                            height);
    
    setDefault.setBounds(addNewPreset.getRight() + buffer,
                          buffer,
                          width,
                          height);
    
    dismissOverlay.setBounds((MainPanelGUI::width * scale) - (PresetPanelGUI::A_B_Copy_width * scale) - buffer,
                              buffer,
                              width,
                              height);
    
    presetsDisplay.setBounds(0, dismissOverlay.getBottom() + buffer, getWidth(), getHeight() - height);
}

//==============================================================================
void PresetDisplayOverlay::buttonClicked(juce::Button* b)
{
    bool rightClick = juce::ModifierKeys::getCurrentModifiers().isPopupMenu();
    
    if (rightClick) {
        
    }
    else {
        if (b == &addNewPreset) {
            setVisible(false);
            
            // display save preset overlay
            juce::Component* overlay = getParentComponent()->findChildWithID("SavePresetOverlayID");

            if (overlay != nullptr) {
                overlay->setVisible(true);
            }
        }
        else if (b == &setDefault) {
            // set default
        }
        else if (b == &dismissOverlay) {
            setVisible(false);
        }
    }
}
