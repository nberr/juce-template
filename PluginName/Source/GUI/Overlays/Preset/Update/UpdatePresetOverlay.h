/*
  ==============================================================================

    UpdatePresetOverlay.h
    Created: 19 Jan 2022 12:34:28pm
    Author:  Nicholas Berriochoa

  ==============================================================================
*/

#pragma once

#include "PanelBase.h"

#include "PresetManager.h"

//==============================================================================
class UpdatePresetOverlay
:   public PanelBase,
    public juce::Button::Listener
{
public:
    //==============================================================================
    UpdatePresetOverlay(PluginNameAudioProcessor* inProcessor, ContextMenu* inContextMenu);
    ~UpdatePresetOverlay() override;
    
    //==============================================================================
    void resized() override;
    
    //==============================================================================
    void buttonClicked(juce::Button*) override;
    
private:
    //==============================================================================
    PresetManager *presetManager;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (UpdatePresetOverlay)
};
