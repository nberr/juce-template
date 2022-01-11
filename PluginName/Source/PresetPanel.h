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
    juce::TextButton undo {"undo"};
    juce::TextButton redo {"redo"};
    
    juce::TextButton prevPreset {"prev"};
    juce::TextButton presetMenu {"default"};
    juce::TextButton nextPreset {"next"};
    
    juce::TextButton presetA    {"A"};
    juce::TextButton presetCopy {"Copy"};
    juce::TextButton presetB    {"B"};
    
    std::vector<juce::TextButton*> buttons = {
        &undo, &redo,
        &prevPreset, &presetMenu, &nextPreset,
        &presetA, &presetCopy, &presetB
    };
};
