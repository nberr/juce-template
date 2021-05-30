/*
  ==============================================================================

    ContextMenu.h
    Created: 30 May 2021 1:56:11am
    Author:  Nicholas Berriochoa

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class ContextMenu
{
public:
    ContextMenu();
    ~ContextMenu();
    
    void showMenu(juce::Component *component);
    
private:
    juce::PopupMenu menu;
    juce::PopupMenu preferences;
    juce::PopupMenu sizes;
};
