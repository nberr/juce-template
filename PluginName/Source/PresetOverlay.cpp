/*
  ==============================================================================

    PresetOverlay.cpp
    Created: 25 Nov 2021 8:57:24am
    Author:  Nicholas Berriochoa

  ==============================================================================
*/

#include "PresetOverlay.h"

PresetOverlay::PresetOverlay(PluginNameAudioProcessor* inProcessor, ContextMenu* inContextMenu)
:   PanelBase(inProcessor, inContextMenu)
{
    setName("PresetOverlay");
    setComponentID("PresetOverlayID");
    
    mAddNewPreset.setButtonText("+");
    mAddNewPreset.setTriggeredOnMouseDown(true);
    mAddNewPreset.addListener(this);
    addAndMakeVisible(&mAddNewPreset);
    
    mSetDefault.setButtonText("default");
    mSetDefault.setTriggeredOnMouseDown(true);
    mSetDefault.addListener(this);
    addAndMakeVisible(&mSetDefault);
    
    mDismissOverlay.setButtonText("x");
    mDismissOverlay.setTriggeredOnMouseDown(true);
    mDismissOverlay.addListener(this);
    addAndMakeVisible(&mDismissOverlay);
}

PresetOverlay::~PresetOverlay()
{
    
}

void PresetOverlay::resized()
{
    float scale = PluginNameInternalParameters::GUIScale;
    int buffer = 5 * scale;
    float width = PresetPanelGUI::A_B_Copy_width * scale,
          height = PresetPanelGUI::A_B_Copy_height * scale;
    
    mAddNewPreset.setBounds(buffer,
                            buffer,
                            width,
                            height);
    
    mSetDefault.setBounds(mAddNewPreset.getRight() + buffer,
                          buffer,
                          width,
                          height);
    
    mDismissOverlay.setBounds((MainPanelGUI::width * scale) - (PresetPanelGUI::A_B_Copy_width * scale) - buffer,
                              buffer,
                              width,
                              height);
}

void PresetOverlay::buttonClicked(juce::Button* b)
{
    bool rightClick = juce::ModifierKeys::getCurrentModifiers().isPopupMenu();
    
    if (rightClick) {
        
    }
    else {
        if (b == &mAddNewPreset) {
            // display save preset overlay
        }
        else if (b == &mSetDefault) {
            // set default
        }
        else if (b == &mDismissOverlay) {
            setVisible(false);
        }
    }
}
