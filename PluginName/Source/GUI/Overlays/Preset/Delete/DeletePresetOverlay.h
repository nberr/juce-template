/*
  ==============================================================================

    DeletePresetOverlay.h
    Created: 19 Jan 2022 12:33:42pm
    Author:  Nicholas Berriochoa

  ==============================================================================
*/

#pragma once

#include "PanelBase.h"

#include "PresetManager.h"

//==============================================================================
class DeletePresetOverlay
:   public PanelBase,
    public juce::Button::Listener
{
public:
    //==============================================================================
    DeletePresetOverlay(PluginNameAudioProcessor* inProcessor, ContextMenu* inContextMenu);
    ~DeletePresetOverlay() override;
    
    //==============================================================================
    void resized() override;
    
    //==============================================================================
    void buttonClicked(juce::Button*) override;
    
private:
    //==============================================================================
    PresetManager *presetManager;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DeletePresetOverlay)
};
