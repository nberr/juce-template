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
    large("large"),
    extraLarge("extra large"),
    XXL("XXL")
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
    else if (*inScale == PluginNameGUI::Scale::extra_large) {
        extraLarge.setTicked(true);
    }
    else if (*inScale == PluginNameGUI::Scale::XXL) {
        XXL.setTicked(true);
    }
    
    small.setAction([this](){
        *mGUIScale = PluginNameGUI::Scale::small;
        
        small.setTicked(true);
        medium.setTicked(false);
        large.setTicked(false);
        extraLarge.setTicked(false);
        XXL.setTicked(false);
    });
    
    
    medium.setAction([this](){
        *mGUIScale = PluginNameGUI::Scale::normal;
        
        small.setTicked(false);
        medium.setTicked(true);
        large.setTicked(false);
        extraLarge.setTicked(false);
        XXL.setTicked(false);
       
    });
    
    
    large.setAction([this](){
        *mGUIScale = PluginNameGUI::Scale::large;
        small.setTicked(false);
        medium.setTicked(false);
        large.setTicked(true);
        extraLarge.setTicked(false);
        XXL.setTicked(false);
    });
    
    extraLarge.setAction([this](){
        *mGUIScale = PluginNameGUI::Scale::extra_large;
        small.setTicked(false);
        medium.setTicked(false);
        large.setTicked(false);
        extraLarge.setTicked(true);
        XXL.setTicked(false);
    });
    
    XXL.setAction([this](){
        *mGUIScale = PluginNameGUI::Scale::XXL;
        small.setTicked(false);
        medium.setTicked(false);
        large.setTicked(false);
        extraLarge.setTicked(false);
        XXL.setTicked(true);
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
        menu.clear();
        menu.addItem(itemClicked);
        buildBaseMenu();
        menu.show();
    }
}

void ContextMenu::buildBaseMenu()
{
    menu.addSeparator();
    sizes.clear();
    sizes.addItem(small);
    sizes.addItem(medium);
    sizes.addItem(large);
    sizes.addItem(extraLarge);
    sizes.addItem(XXL);
    
    preferences.clear();
    preferences.addItem("Dark Mode", [](){});
    preferences.addSubMenu("Size", sizes);
    
    menu.addSubMenu("Preferences", preferences);
    menu.addSeparator();
    menu.addItem("PluginName version 1.0", [](){});
}
