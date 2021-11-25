/*
  ==============================================================================

    ContextMenu.cpp
    Created: 25 Nov 2021 8:57:56am
    Author:  Nicholas Berriochoa

  ==============================================================================
*/

#include "ContextMenu.h"

#include "PluginEditor.h"

ContextMenu::ContextMenu(float* inScale)
:   mGUIScale(inScale),
    small("small"),
    medium("medium"),
    large("large")
{
    setName("ContextMenu");
    setComponentID("ContextMenuID");
    
    if (*inScale == PluginNameGUI::Scale::small) {
        small.setTicked(true);
    }
    else if (*inScale == PluginNameGUI::Scale::normal) {
        medium.setTicked(true);
    }
    else if (*inScale == PluginNameGUI::Scale::large) {
        large.setTicked(true);
    }
    
    small.setAction([this](){
        *mGUIScale = PluginNameGUI::Scale::small;
        
        small.setTicked(true);
        medium.setTicked(false);
        large.setTicked(false);
    });
    
    
    medium.setAction([this](){
        *mGUIScale = PluginNameGUI::Scale::normal;
        
        small.setTicked(false);
        medium.setTicked(true);
        large.setTicked(false);
       
    });
    
    
    large.setAction([this](){
        *mGUIScale = PluginNameGUI::Scale::large;
        small.setTicked(false);
        medium.setTicked(false);
        large.setTicked(true);
    });
    
    
}

ContextMenu::~ContextMenu()
{
    
}

void ContextMenu::showMenu(const juce::String itemClicked)
{
    if (itemClicked == "MainPanel") {
        menu.clear();
        
        menu.addItem(itemClicked, []{});
        
        buildBaseMenu();
        
        //menu.show();
    }
    else if (itemClicked == "PresetPanel") {
        menu.clear();
        
        menu.addItem(itemClicked, []{});
        
        buildBaseMenu();
        
        //menu.show();
    }
    else if (itemClicked == "NewPreset") {
        menu.clear();
        menu.addItem(itemClicked);
        buildBaseMenu();
        //menu.show();
    }
    else {
        menu.clear();
        menu.addItem(itemClicked);
        buildBaseMenu();
        //menu.show();
    }
}

void ContextMenu::buildBaseMenu()
{
    menu.addSeparator();
    sizes.clear();
    sizes.addItem(small);
    sizes.addItem(medium);
    sizes.addItem(large);
    
    preferences.clear();
    preferences.addItem("Dark Mode", [](){});
    preferences.addSubMenu("Size", sizes);
    
    menu.addSubMenu("Preferences", preferences);
    menu.addSeparator();
    menu.addItem("PluginName version 1.0", [](){});
}
