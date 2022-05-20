/*
  ==============================================================================

    DeletePresetOverlay.cpp
    Created: 19 Jan 2022 12:33:42pm
    Author:  Nicholas Berriochoa

  ==============================================================================
*/

#include "DeletePresetOverlay.h"

//==============================================================================
DeletePresetOverlay::DeletePresetOverlay(PluginNameAudioProcessor* inProcessor, ContextMenu* inContextMenu)
:   PanelBase(inProcessor, inContextMenu)
{
    setName("DeletePresetOverlay");
    setComponentID("DeletePresetOverlayID");
    
    presetManager = processor->getPresetManager();
}

DeletePresetOverlay::~DeletePresetOverlay()
{
    
}

//==============================================================================
void DeletePresetOverlay::resized()
{
    
}

//==============================================================================
void DeletePresetOverlay::buttonClicked(juce::Button*)
{
    
}
