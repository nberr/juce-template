/*
  ==============================================================================

    ContextMenu.h
    Created: 30 May 2021 1:56:11am
    Author:  Nicholas Berriochoa

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#include "InterfaceDefines.h"

class ContextMenu
: public juce::Component
{
public:
    
    // TODO: each item in the context menu should have an ID so triggers can be set properly
    enum ItemID {
        GUI_Small,
        GUI_Medium,
        GUI_Large,
        GUI_Extra_Large,
        GUI_XXL
    };
    
    ContextMenu(float *inScale);
    ~ContextMenu();
    
    void showMenu(const juce::String itemClicked);
    
    void buildBaseMenu();
    
    float *mGUIScale;
    
private:
    juce::PopupMenu menu;
    juce::PopupMenu preferences;
    juce::PopupMenu sizes;
    
    juce::PopupMenu::Item small;
    juce::PopupMenu::Item medium;
    juce::PopupMenu::Item large;
    juce::PopupMenu::Item extraLarge;
    juce::PopupMenu::Item XXL;

    
};
