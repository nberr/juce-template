/*
  ==============================================================================

    SavePresetOverlay.h
    Created: 19 Jan 2022 12:22:29pm
    Author:  Nicholas Berriochoa

  ==============================================================================
*/

#pragma once

#include "OverlayBase.h"

#include "PresetManager.h"

//==============================================================================
class SavePresetOverlay
:   public OverlayBase,
    public juce::Button::Listener
{
public:
    //==============================================================================
    SavePresetOverlay(PluginNameAudioProcessor* inProcessor, ContextMenu* inContextMenu);
    ~SavePresetOverlay() override;
    
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
    std::vector<juce::Button*> buttons = {
        &close,
        &save,
        &cancel
    };
    
    //==============================================================================
    juce::Label saveNewPreset {"Save New Preset"};
    juce::Label presetName {"Preset Name"};
    juce::Label notesLabel {"Notes (optional)"};
    juce::Label makeDefault {"Make Default"};
    juce::Label presetNameRequired {"Preset Name Is Required"};
    
    //==============================================================================
    std::vector<juce::Label*> labels = {
        &saveNewPreset,
        &presetName,
        &notesLabel,
        &makeDefault,
        &presetNameRequired
    };
    
    //==============================================================================
    juce::TextEditor presetNameInput;
    juce::TextEditor notesInput;
    juce::TextButton makeDefaultButton;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SavePresetOverlay)
};
