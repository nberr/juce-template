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
:   mGUIScale(inScale),
    small("small"),
    medium("medium"),
    large("large")
{
    setName("ContextMenu");
    
    if (*inScale == GUI_Scale::small) {
        small.setTicked(true);
    }
    else if (*inScale == GUI_Scale::normal) {
        medium.setTicked(true);
    }
    else if (*inScale == GUI_Scale::large) {
        large.setTicked(true);
    }
    
    small.setAction([this](){
        *mGUIScale = GUI_Scale::small;
        
        small.setTicked(true);
        medium.setTicked(false);
        large.setTicked(false);
    });
    
    
    medium.setAction([this](){
        *mGUIScale = GUI_Scale::normal;
        
        small.setTicked(false);
        medium.setTicked(true);
        large.setTicked(false);
       
    });
    
    
    large.setAction([this](){
        *mGUIScale = GUI_Scale::large;
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
        
        menu.show();
    }
    else if (itemClicked == "PresetPanel") {
        menu.clear();
        
        menu.addItem(itemClicked, []{});
        
        buildBaseMenu();
        
        menu.show();
    }
    else if (itemClicked == "NewPreset") {
        menu.clear();
        menu.addItem(itemClicked);
        buildBaseMenu();
        menu.show();
    }
    else {
        DBG(itemClicked);
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
