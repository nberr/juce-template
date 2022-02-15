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
    void savePreset(juce::String name, juce::String notes, bool shouldBeDefault);
    void updatePreset(juce::String name);
    
    void loadPreset(juce::String name);
    void loadNextPreset();
    void loadPreviousPreset();
    
    //==============================================================================
    PresetViewItem* getRootItem();
    
    juce::String getCurrentPresetName();
    
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
    juce::AudioProcessor* processor;
    juce::AudioProcessorValueTreeState *parameters;
    
    //==============================================================================
    int currentPresetIndex = -1;
    juce::String currentPresetName = "";
    
    //==============================================================================
    const juce::String dir_sep = juce::File::getSeparatorString();
    const juce::String pluginDirectory = juce::File::getSpecialLocation(juce::File::userMusicDirectory).getFullPathName()
                                         + dir_sep + JucePlugin_Manufacturer
                                         + dir_sep + JucePlugin_Name;
    juce::File presetsFile = juce::File(pluginDirectory + dir_sep + "presets.xml");
    
    //==============================================================================
    // connection between the presetsFile file and the PresetManager
    void initializePresetsTree();
    
    juce::ValueTree presetsTree;
    
    //==============================================================================
    // used to display the presets
    void initializeRootViewItem();
    void populateUserPresets(PresetViewItem* userPresets);
    void populateFactoryPresets(std::vector<PresetViewItem *>& factoryPresets);
    
    PresetViewItem *rootViewItem, *userPresets;
    std::vector<PresetViewItem *> factoryPresets;
    
    //==============================================================================
    // the actual preset values
    void initializePresetsXmlData();
    
    std::vector<juce::XmlElement> presetsXmlData;
    int numUserPresets = 0;
    
    //==============================================================================
    // quick swap functionality
    juce::MemoryBlock presetA;
    juce::MemoryBlock presetB;
    
    bool fromToggle = false;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PresetManager)
};
