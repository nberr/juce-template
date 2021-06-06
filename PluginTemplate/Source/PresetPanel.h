/*
  ==============================================================================

    PresetPanel.h
    Created: 12 Apr 2021 7:37:19pm
    Author:  Nicholas Berriochoa

  ==============================================================================
*/

#pragma once

#include "PanelBase.h"

class PresetPanel
:   public PanelBase,
    public juce::Button::Listener,
    public juce::ComboBox::Listener
{
public:
    PresetPanel(PluginNameAudioProcessor *inProcessor, ContextMenu* inContextMenu);
    ~PresetPanel();
    
    void paint(juce::Graphics& g) override;
        
    void buttonClicked(juce::Button*) override;
    void comboBoxChanged(juce::ComboBox* comboBoxThatHasChanged) override;
private:
    void displaySaveAsPopup();
        
    void updatePresetComboBox();
        
    std::unique_ptr<juce::ComboBox> mPresetDisplay;
        
    std::unique_ptr<juce::TextButton> mNewPreset, mSavePreset, mSaveAsPreset;
};
