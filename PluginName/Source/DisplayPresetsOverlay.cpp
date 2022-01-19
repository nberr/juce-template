/*
  ==============================================================================

    DisplayPresetsOverlay.cpp
    Created: 25 Nov 2021 8:57:24am
    Author:  Nicholas Berriochoa

  ==============================================================================
*/

#include "DisplayPresetsOverlay.h"

//==============================================================================
DisplayPresetsOverlay::DisplayPresetsOverlay(PluginNameAudioProcessor* inProcessor, ContextMenu* inContextMenu)
:   PanelBase(inProcessor, inContextMenu)
{
    setName("DisplayPresetsOverlay");
    setComponentID("DisplayPresetsOverlayID");
    
    presetManager = mProcessor->getPresetManager();
    
    isOverlay = true;
    
    // initialize each button and add them to the scene
    for (juce::TextButton* button : buttons) {
        button->setTriggeredOnMouseDown(true);
        button->addListener(this);
        addAndMakeVisible(button);
    }
}

DisplayPresetsOverlay::~DisplayPresetsOverlay()
{
    
}

//==============================================================================
void DisplayPresetsOverlay::resized()
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
}

//==============================================================================
void DisplayPresetsOverlay::buttonClicked(juce::Button* b)
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
