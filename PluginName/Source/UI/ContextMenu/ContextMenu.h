/*
  ==============================================================================

    ContextMenu.h
    Created: 25 Nov 2021 8:57:56am
    Author:  Nicholas Berriochoa

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#include "PluginProcessor.h"

//==============================================================================
class ContextMenu
: public juce::Component
{
public:
    //==============================================================================
    ContextMenu(PluginNameAudioProcessor* procssor);
    ~ContextMenu();
    
    //==============================================================================
    void showMenu(const juce::String itemClicked);
    void buildBaseMenu();
    
    //==============================================================================
    void showPresetMenu(const juce::String itemClicked, bool isUserPreset);
        
private:
    //==============================================================================
    PluginNameAudioProcessor* processor;
    
    //==============================================================================
    juce::PopupMenu menu;
    juce::PopupMenu preferences;
    juce::PopupMenu sizes;
    
    //==============================================================================
    void initMenuActions();
    
    juce::PopupMenu::Item small {"Small"};
    juce::PopupMenu::Item standard {"Standard"};
    juce::PopupMenu::Item large {"Large"};
    juce::PopupMenu::Item extra_large {"Extra Large"};
    juce::PopupMenu::Item xxl {"XXL"};
    
    juce::PopupMenu::Item showSidePanel {"Always Show Side Panel"};
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ContextMenu)
};
