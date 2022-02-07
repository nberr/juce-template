/*
  ==============================================================================

    UpdatePresetOverlay.cpp
    Created: 19 Jan 2022 12:34:28pm
    Author:  Nicholas Berriochoa

  ==============================================================================
*/

#include "UpdatePresetOverlay.h"

//==============================================================================
UpdatePresetOverlay::UpdatePresetOverlay(PluginNameAudioProcessor* processor, ContextMenu* contextMenu)
:   PanelBase(processor, contextMenu)
{
    setName("UpdatePresetOverlay");
    setComponentID("UpdatePresetOverlayID");
    
    presetManager = processor->getPresetManager();
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
