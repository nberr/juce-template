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
    
    mAddNewPreset.setBounds(0 * scale, 0, 50, 50);
    mSetDefault.setBounds(0, 50, 50, 50);
    mDismissOverlay.setBounds(0, 100, 50, 50);
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
