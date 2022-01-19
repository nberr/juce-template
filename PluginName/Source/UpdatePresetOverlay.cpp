/*
  ==============================================================================

    UpdatePresetOverlay.cpp
    Created: 19 Jan 2022 12:34:28pm
    Author:  Nicholas Berriochoa

  ==============================================================================
*/

#include "UpdatePresetOverlay.h"

//==============================================================================
UpdatePresetOverlay::UpdatePresetOverlay(PluginNameAudioProcessor* inProcessor, ContextMenu* inContextMenu)
:   PanelBase(inProcessor, inContextMenu)
{
    setName("UpdatePresetOverlay");
    setComponentID("UpdatePresetOverlayID");
    
    presetManager = mProcessor->getPresetManager();
}

UpdatePresetOverlay::~UpdatePresetOverlay()
{
    
}

//==============================================================================
void UpdatePresetOverlay::resized()
{
    
}

//==============================================================================
void UpdatePresetOverlay::buttonClicked(juce::Button*)
{
    
}
