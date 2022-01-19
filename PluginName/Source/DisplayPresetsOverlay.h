/*
  ==============================================================================

    DisplayPresetsOverlay.h
    Created: 25 Nov 2021 8:57:24am
    Author:  Nicholas Berriochoa

  ==============================================================================
*/

#pragma once

#include "PanelBase.h"

#include "PresetManager.h"

//==============================================================================
class DisplayPresetsOverlay
:   public PanelBase,
    public juce::Button::Listener
{
public:
    //==============================================================================
    DisplayPresetsOverlay(PluginNameAudioProcessor* inProcessor, ContextMenu* inContextMenu);
    ~DisplayPresetsOverlay();
    
    //==============================================================================
    void resized() override;
    
    //==============================================================================
    void buttonClicked(juce::Button*) override;
    
private:
    //==============================================================================
    PresetManager *presetManager;
    
    //==============================================================================
    juce::TextButton addNewPreset {"+"};
    juce::TextButton setDefault {"default"};
    juce::TextButton dismissOverlay {"x"};
    
    //==============================================================================
    std::vector<juce::TextButton*> buttons = {
        &addNewPreset,
        &setDefault,
        &dismissOverlay
    };
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DisplayPresetsOverlay)
};
