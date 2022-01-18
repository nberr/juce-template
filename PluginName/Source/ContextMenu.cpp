/*
  ==============================================================================

    ContextMenu.cpp
    Created: 25 Nov 2021 8:57:56am
    Author:  Nicholas Berriochoa

  ==============================================================================
*/

#include "ContextMenu.h"

#include "PluginNameSettings.h" // for GUIScale
#include "PluginNameGUI.h" // for Scale sizes

//==============================================================================
ContextMenu::ContextMenu()
:   small("small"),
    medium("medium"),
    large("large")
{
    setName("ContextMenu");
    setComponentID("ContextMenuID");
    
    float *scale = &PluginNameSettings::GUIScale;
    
    if (*scale == PluginNameGUI::Scale::small) {
        small.setTicked(true);
    }
    else if (*scale == PluginNameGUI::Scale::normal) {
        medium.setTicked(true);
    }
    else if (*scale == PluginNameGUI::Scale::large) {
        large.setTicked(true);
    }
    
    small.setAction([this, scale](){
        *scale = PluginNameGUI::Scale::small;
        
        small.setTicked(true);
        medium.setTicked(false);
        large.setTicked(false);
    });
    
    
    medium.setAction([this, scale](){
        *scale = PluginNameGUI::Scale::normal;
        
        small.setTicked(false);
        medium.setTicked(true);
        large.setTicked(false);
    });
    
    
    large.setAction([this, scale](){
        *scale = PluginNameGUI::Scale::large;
        small.setTicked(false);
        medium.setTicked(false);
        large.setTicked(true);
    });
}

ContextMenu::~ContextMenu()
{
    
}

//==============================================================================
void ContextMenu::showMenu(const juce::String itemClicked)
{
    if (itemClicked == "MainPanel") {
        menu.clear();
        
        menu.addItem(itemClicked, []{});
        buildBaseMenu();
        menu.showMenuAsync(juce::PopupMenu::Options().withMinimumWidth (100)
                                   .withMaximumNumColumns (3)
                                   .withTargetComponent (this).withMousePosition());
    }
    else if (itemClicked == "PresetPanel") {
        menu.clear();
        
        menu.addItem(itemClicked, []{});
        
        buildBaseMenu();
        
        menu.showMenuAsync(juce::PopupMenu::Options().withMinimumWidth (100)
                                   .withMaximumNumColumns (3)
                                   .withTargetComponent (this).withMousePosition());
    }
    else if (itemClicked == "NewPreset") {
        menu.clear();
        menu.addItem(itemClicked);
        buildBaseMenu();
        menu.showMenuAsync(juce::PopupMenu::Options().withMinimumWidth (100)
                                   .withMaximumNumColumns (3)
                                   .withTargetComponent (this).withMousePosition());
    }
    else {
        menu.clear();
        menu.addItem(itemClicked);
        buildBaseMenu();

        menu.showMenuAsync(juce::PopupMenu::Options().withMinimumWidth (100)
                                   .withMaximumNumColumns (3)
                                   .withTargetComponent (this).withMousePosition());
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
