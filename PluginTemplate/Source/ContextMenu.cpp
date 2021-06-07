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
    
    // TODO: each item in the context menu should have an ID so triggers can be set properly
    
    if (*inScale == 0.8f) {
        small.setTicked(true);
    }
    else if (*inScale == 1.0f) {
        medium.setTicked(true);
    }
    else if (*inScale == 1.2f) {
        large.setTicked(true);
    }
    
    small.setAction([this](){
        *mGUIScale = 0.8;
        
        small.setTicked(true);
        medium.setTicked(false);
        large.setTicked(false);
    });
    
    
    medium.setAction([this](){
        *mGUIScale = 1.0;
        
        small.setTicked(false);
        medium.setTicked(true);
        large.setTicked(false);
       
    });
    
    
    large.setAction([this](){
        *mGUIScale = 1.2;
        small.setTicked(false);
        medium.setTicked(false);
        large.setTicked(true);
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
    menu.addItem(small);
    menu.addItem(medium);
    menu.addItem(large);
}
