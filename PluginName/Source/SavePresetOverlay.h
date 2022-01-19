/*
  ==============================================================================

    SavePresetOverlay.h
    Created: 19 Jan 2022 12:22:29pm
    Author:  Nicholas Berriochoa

  ==============================================================================
*/

#pragma once

#include "PanelBase.h"

#include "PresetManager.h"

//==============================================================================
class SavePresetOverlay
:   public PanelBase,
    public juce::Button::Listener
{
public:
    //==============================================================================
    SavePresetOverlay(PluginNameAudioProcessor* inProcessor, ContextMenu* inContextMenu);
    ~SavePresetOverlay();
    
    //==============================================================================
    void resized() override;
    
    //==============================================================================
    void buttonClicked(juce::Button*) override;
    
private:
    //==============================================================================
    PresetManager *presetManager;
    
    //==============================================================================
    juce::TextButton close {"x"};
    juce::TextButton save {"save"};
    juce::TextButton cancel {"cancel"};
    
    //==============================================================================
    std::vector<juce::TextButton*> buttons = {
        &close,
        &save,
        &cancel
    };
    
    //==============================================================================
    juce::Label saveNewPreset {"Save New Preset"};
    juce::Label presetName {"Preset Name"};
    juce::Label notes {"Notes (optional)"};
    juce::Label makeDefault {"Make Default"};
    
    //==============================================================================
    juce::TextEditor presetNameInput;
    juce::TextEditor notesInput;
    juce::TextButton makeDefaultButton;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SavePresetOverlay)
};
