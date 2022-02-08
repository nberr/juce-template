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
    void getXmlForPreset(juce::XmlElement* element);
    void loadPresetForXml(juce::XmlElement* element);
    
    //==============================================================================
    int getNumberOfPresets();
    juce::String getPresetName(int index);
    juce::String getPresetPath();
    
    //==============================================================================
    void createNewPreset();
    void savePreset();
    void saveAsPreset(juce::String name, juce::String notes);
    void loadPreset(int index);
    
    //==============================================================================
    bool getIsCurrentPresetSaved();
    juce::String getCurrentPresetName();
    
    //==============================================================================
    void populateUserPresets(PresetViewItem* userPresets);
    void populateFactoryPresets(std::vector<PresetViewItem *>& factoryPresets);
    
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
    void storeLocalPreset();
    
    //==============================================================================
    juce::AudioProcessor* processor;
    juce::AudioProcessorValueTreeState *parameters;
    
    //==============================================================================
    bool mCurrentPresetIsSaved;
    
    //==============================================================================
    juce::File mCurrentlyLoadedPreset;
    juce::Array<juce::File> mLocalPresets;
    
    //==============================================================================
    juce::String mCurrentPresetName;
    // juce::String presetNotes;
    juce::String mPresetDirectory;
    
    //==============================================================================
    juce::XmlElement* mCurrentPresetXml;
    
    //==============================================================================
    juce::MemoryBlock presetA;
    juce::MemoryBlock presetB;
    
    bool fromToggle = false;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PresetManager)
};
