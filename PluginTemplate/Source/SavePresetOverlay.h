/*
  ==============================================================================

    SavePresetOverlay.h
    Created: 18 Jun 2021 8:14:40pm
    Author:  Nicholas Berriochoa

  ==============================================================================
*/

#pragma once

#include "PanelBase.h"

class SavePresetOverlay
:   public PanelBase, public juce::Button::Listener
{
public:
    SavePresetOverlay(PluginNameAudioProcessor* inProcessor, ContextMenu* inContextMenu);
    ~SavePresetOverlay();
    
    void resized() override;
    void buttonClicked(juce::Button* b) override;
    
private:
    juce::Label mPresetNameLabel;
    juce::TextEditor mPresetNameInput;
    
    juce::TextButton mSavePreset;
    juce::TextButton mCancel;
};


