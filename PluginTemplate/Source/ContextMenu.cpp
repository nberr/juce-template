/*
  ==============================================================================

    ContextMenu.cpp
    Created: 30 May 2021 1:56:11am
    Author:  Nicholas Berriochoa

  ==============================================================================
*/

#include "ContextMenu.h"

#include "PluginEditor.h"

ContextMenu::ContextMenu(float* inScale)
:   mGUIScale(inScale)
{
    setName("ContextMenu");
    
    // TODO: each item in the context menu should have an ID so triggers can be set properly
    
    juce::PopupMenu::Item small("Small");
    small.setAction([this](){
        
        *mGUIScale = 0.8;
       
    });
    
    juce::PopupMenu::Item medium("Medium");
    medium.setAction([this](){
        
        *mGUIScale = 1.0;
       
    });
    medium.setTicked();
    
    juce::PopupMenu::Item large("Large");
    large.setAction([this](){
        *mGUIScale = 1.2;
    });
    
    sizes.addItem(small);
    sizes.addItem(medium);
    sizes.addItem(large);
    
    preferences.addItem("Dark Mode", [](){});
    preferences.addSubMenu("Size", sizes);
    
    menu.addSubMenu("Preferences", preferences);
    menu.addSeparator();
    menu.addItem("PluginName version 1.0", [](){});
}

ContextMenu::~ContextMenu()
{
    
}

void ContextMenu::showMenu(const juce::String itemClicked)
{
    if (itemClicked == "MainPanel") {
        menu.show();
    }
    else if (itemClicked == "PresetPanel") {
        menu.addItem("PresetPanel", [](){});
        menu.show();
    }
    else if (itemClicked == "NewPreset") {
        menu.addItem(itemClicked);
        menu.show();
    }
    else {
        DBG(itemClicked);
    }
}
