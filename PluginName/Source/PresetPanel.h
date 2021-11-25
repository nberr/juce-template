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
    juce::TextButton mPresetMenu;
    juce::TextButton mPrevPreset;
    juce::TextButton mNextPreset;
    
    juce::TextButton mUndo;
    juce::TextButton mRedo;
    
    juce::TextButton mPresetA;
    juce::TextButton mPresetB;
    juce::TextButton mPresetCopy;
};
