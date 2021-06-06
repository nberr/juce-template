/*
  ==============================================================================

    ContextMenu.cpp
    Created: 30 May 2021 1:56:11am
    Author:  Nicholas Berriochoa

  ==============================================================================
*/

#include "ContextMenu.h"

#include "PluginEditor.h"

ContextMenu::ContextMenu()
{
    juce::PopupMenu::Item small("Small");
    small.setAction([](){});
    
    juce::PopupMenu::Item medium("Medium");
    medium.setAction([](){});
    medium.setTicked();
    
    juce::PopupMenu::Item large("Large");
    large.setAction([](){});
    
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
