/*
  ==============================================================================

    PresetDisplayOverlay.h
    Created: 25 Nov 2021 8:57:24am
    Author:  Nicholas Berriochoa

  ==============================================================================
*/

#pragma once

#include "OverlayBase.h"

#include "PresetManager.h"
#include "PresetViewItem.h"
#include "PresetViewManager.h"

//==============================================================================
class PresetDisplayOverlay
:   public OverlayBase,
    public juce::Button::Listener
{
public:
    //==============================================================================
    PresetDisplayOverlay(PluginNameAudioProcessor* inProcessor, ContextMenu* inContextMenu);
    ~PresetDisplayOverlay();
    
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
    
    PresetViewItem *rootViewItem;
    PresetViewItem *userPresets, *factoryPresets;
    
    juce::TreeView presetsDisplay;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PresetDisplayOverlay)
};