/*
  ==============================================================================

    PresetOverlay.h
    Created: 9 Jun 2021 5:47:45pm
    Author:  Nicholas Berriochoa

  ==============================================================================
*/

#pragma once

#include "PanelBase.h"

class PresetOverlay
:   public PanelBase,
    public juce::Button::Listener
{
public:
    PresetOverlay(PluginNameAudioProcessor* inProcessor, ContextMenu* inContextMenu);
    ~PresetOverlay();
    
    void resized() override;
    
    void buttonClicked(juce::Button*) override;
    
private:
    juce::Array<juce::PropertyComponent*> getPresets();
    juce::Array<juce::PropertyComponent*> getUserPresets();
    
    juce::TextButton mAddNewPreset;
    juce::TextButton mSetDefault;
    juce::TextButton mDismissOverlay;
    
    juce::ConcertinaPanel mPresetDisplay;
    
};
