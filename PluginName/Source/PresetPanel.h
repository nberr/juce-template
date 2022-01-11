/*
  ==============================================================================

    PresetPanel.h
    Created: 25 Nov 2021 8:56:36am
    Author:  Nicholas Berriochoa

  ==============================================================================
*/

#pragma once

#include "PanelBase.h"

class PresetPanel
:   public PanelBase,
    public juce::Button::Listener
{
public:
    PresetPanel(PluginNameAudioProcessor* inProcessor, ContextMenu* inContextMenu);
    ~PresetPanel();
    
    void resized() override;
        
    void buttonClicked(juce::Button*) override;
private:
    juce::TextButton presetMenu {"default"};
    juce::TextButton prevPreset {"prev"};
    juce::TextButton nextPreset {"next"};
    
    juce::TextButton undo {"undo"};
    juce::TextButton redo {"redo"};
    
    juce::TextButton presetA    {"A"};
    juce::TextButton presetB    {"B"};
    juce::TextButton presetCopy {"Copy"};
};
