/*
  ==============================================================================

    ContextMenu.cpp
    Created: 30 May 2021 1:56:11am
    Author:  Nicholas Berriochoa

  ==============================================================================
*/

#include "ContextMenu.h"

ContextMenu::ContextMenu()
{
    sizes.addItem("Small", [](){});
    sizes.addItem("Medium", [](){});
    sizes.addItem("Large", [](){});
    
    preferences.addItem("Dark Mode", [](){});
    preferences.addSubMenu("Size", sizes);
    
    menu.addSubMenu("Preferences", preferences);
    menu.addSeparator();
    menu.addItem("PluginName version 1.0", [](){});
}

ContextMenu::~ContextMenu()
{
    
}

void ContextMenu::showMenu(juce::Component *component)
{
    if (component->getName() == "MainPanel") {
        menu.show();
    }
    else if (component->getName() == "PresetPanel") {
        menu.addItem("PresetPanel", [](){});
        menu.show();
    }
}
