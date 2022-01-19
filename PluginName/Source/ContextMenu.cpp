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
#include "SettingsManager.h"

//==============================================================================
ContextMenu::ContextMenu(PluginNameAudioProcessor* inProcssor)
{
    setName("ContextMenu");
    setComponentID("ContextMenuID");
    
    mProcessor = inProcssor;
    
    // set the size menu based on the current scale
    float scale = mProcessor->settings.getChild(PluginNameSettings::PNS_GUIScale).getProperty(juce::Identifier("value"));
    if (scale == PluginNameGUI::Scale::small) {
        small.setTicked(true);
    }
    else if (scale == PluginNameGUI::Scale::standard) {
        standard.setTicked(true);
    }
    else if (scale == PluginNameGUI::Scale::large) {
        large.setTicked(true);
    }
    else if (scale == PluginNameGUI::Scale::extra_large) {
        extra_large.setTicked(true);
    }
    else if (scale == PluginNameGUI::Scale::XXL) {
        xxl.setTicked(true);
    }
    
    initMenuSize();
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
    sizes.addItem(standard);
    sizes.addItem(large);
    sizes.addItem(extra_large);
    sizes.addItem(xxl);
    
    preferences.clear();
    preferences.addItem("Dark Mode", [](){});
    preferences.addSubMenu("Size", sizes);
    
    menu.addSubMenu("Preferences", preferences);
    menu.addSeparator();
    menu.addItem("PluginName version 1.0", [](){});
}

//==============================================================================
void ContextMenu::initMenuSize()
{
    SettingsManager *sm = mProcessor->getSettingsManager();
    
    small.setAction([this, sm](){
        juce::ValueTree guiScale = mProcessor->settings.getChild(PluginNameSettings::PNS_GUIScale);
        guiScale.setProperty(juce::Identifier("value"), PluginNameGUI::Scale::small, nullptr);
        
        small.setTicked(true);
        standard.setTicked(false);
        large.setTicked(false);
        extra_large.setTicked(false);
        xxl.setTicked(false);
        
        sm->saveSettings();
    });
    
    
    standard.setAction([this, sm](){
        juce::ValueTree guiScale = mProcessor->settings.getChild(PluginNameSettings::PNS_GUIScale);
        guiScale.setProperty(juce::Identifier("value"), PluginNameGUI::Scale::standard, nullptr);
        
        small.setTicked(false);
        standard.setTicked(true);
        large.setTicked(false);
        extra_large.setTicked(false);
        xxl.setTicked(false);
        
        sm->saveSettings();
    });
    
    
    large.setAction([this, sm](){
        juce::ValueTree guiScale = mProcessor->settings.getChild(PluginNameSettings::PNS_GUIScale);
        guiScale.setProperty(juce::Identifier("value"), PluginNameGUI::Scale::large, nullptr);
        
        small.setTicked(false);
        standard.setTicked(false);
        large.setTicked(true);
        extra_large.setTicked(false);
        xxl.setTicked(false);
        
        sm->saveSettings();
    });
    
    extra_large.setAction([this, sm](){
        juce::ValueTree guiScale = mProcessor->settings.getChild(PluginNameSettings::PNS_GUIScale);
        guiScale.setProperty(juce::Identifier("value"), PluginNameGUI::Scale::extra_large, nullptr);
        
        small.setTicked(false);
        standard.setTicked(false);
        large.setTicked(false);
        extra_large.setTicked(true);
        xxl.setTicked(false);
        
        sm->saveSettings();
    });
    
    xxl.setAction([this, sm](){
        juce::ValueTree guiScale = mProcessor->settings.getChild(PluginNameSettings::PNS_GUIScale);
        guiScale.setProperty(juce::Identifier("value"), PluginNameGUI::Scale::XXL, nullptr);
        
        small.setTicked(false);
        standard.setTicked(false);
        large.setTicked(false);
        extra_large.setTicked(false);
        xxl.setTicked(true);
        
        sm->saveSettings();
    });
}
