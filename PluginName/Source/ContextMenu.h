/*
  ==============================================================================

    ContextMenu.h
    Created: 25 Nov 2021 8:57:56am
    Author:  Nicholas Berriochoa

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//

//==============================================================================
class ContextMenu
: public juce::Component
{
public:
    //==============================================================================
    ContextMenu(float *inScale);
    ~ContextMenu();
    
    //==============================================================================
    // TODO: each item in the context menu should have an ID so triggers can be set properly
    enum ItemID {
        GUI_Small,
        GUI_Medium,
        GUI_Large,
        GUI_XL,
        GUI_XXL
    };
    
    //==============================================================================
    void showMenu(const juce::String itemClicked);
    void buildBaseMenu();
        
private:
    //==============================================================================
    juce::PopupMenu menu;
    juce::PopupMenu preferences;
    juce::PopupMenu sizes;
    
    //==============================================================================
    juce::PopupMenu::Item small;
    juce::PopupMenu::Item medium;
    juce::PopupMenu::Item large;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ContextMenu)
};
