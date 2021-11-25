/*
  ==============================================================================

    PresetOverlay.h
    Created: 25 Nov 2021 8:57:24am
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
    juce::TextButton mAddNewPreset;
    juce::TextButton mSetDefault;
    juce::TextButton mDismissOverlay;
};
