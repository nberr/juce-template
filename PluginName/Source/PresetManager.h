/*
  ==============================================================================

    PresetManager.h
    Created: 25 Nov 2021 9:02:19am
    Author:  Nicholas Berriochoa

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#include "PresetViewItem.h"

#define PRESET_FILE_EXTENSION ".xml"

//==============================================================================
class PresetManager
{
public:
    //==============================================================================
    PresetManager(juce::AudioProcessor* processor, juce::AudioProcessorValueTreeState* parameters);
    ~PresetManager();
    
    //==============================================================================
    // void getXmlForPreset(juce::XmlElement* element);
    // void loadPresetForXml(juce::XmlElement* element);
    
    //==============================================================================
    // int getNumberOfPresets();
    // juce::String getPresetName(int index);
    // juce::String getPresetPath();
    
    //==============================================================================
    // void createNewPreset();
    // void savePreset();
    void saveAsPreset(juce::String name, juce::String notes);
    void loadPreset(juce::String name);
    
    //==============================================================================
    // bool getIsCurrentPresetSaved();
    // juce::String getCurrentPresetName();
    
    //==============================================================================
    void populateUserPresets(PresetViewItem* userPresets);
    void populateFactoryPresets(std::vector<PresetViewItem *>& factoryPresets);
    PresetViewItem* getRootItem();
    void addUserPreset(PresetViewItem* item);
    
    //==============================================================================
    void updateQuickPreset();
    void toggleQuickPreset();
    void copyQuickPreset();
    
    enum QuickPreset {
        Preset_A = 0,
        Preset_B
    };
    
    QuickPreset quickPresetInUse = QuickPreset::Preset_A;
    
private:
    //==============================================================================
    // void storeLocalPreset();
    
    //==============================================================================
    juce::AudioProcessor* processor;
    juce::AudioProcessorValueTreeState *parameters;
    
    //==============================================================================
    juce::String currentPresetName;
    bool currentPresetIsSaved;
    
    //==============================================================================
    juce::File currentlyLoadedPreset;
    juce::Array<juce::File> localPresets;
    
    //==============================================================================
    // juce::String currentPresetName;
    juce::String presetDirectory;
    
    //==============================================================================
    juce::XmlElement* currentPresetXml;
    
    //==============================================================================
    juce::MemoryBlock presetA;
    juce::MemoryBlock presetB;
    
    bool fromToggle = false;
    
    //==============================================================================
    PresetViewItem *rootViewItem, *userPresets;
    std::vector<PresetViewItem *> factoryPresets;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PresetManager)
};
