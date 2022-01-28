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
    PresetManager(juce::AudioProcessor* inProcssor, juce::AudioProcessorValueTreeState* inParameters);
    ~PresetManager();
    
    //==============================================================================
    void getXmlForPreset(juce::XmlElement* inElement);
    void loadPresetForXml(juce::XmlElement* inElement);
    
    //==============================================================================
    int getNumberOfPresets();
    juce::String getPresetName(int inPresetIndex);
    juce::String getPresetPath();
    
    //==============================================================================
    void createNewPreset();
    void savePreset();
    void saveAsPreset(juce::String inPresetName, juce::String notes);
    void loadPreset(int inPresetIndex);
    
    //==============================================================================
    bool getIsCurrentPresetSaved();
    juce::String getCurrentPresetName();
    
    //==============================================================================
    void populateViewItem(PresetViewItem* item);
    
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
    juce::AudioProcessor* mProcessor;
    juce::AudioProcessorValueTreeState *parameters;
    
    //==============================================================================
    bool mCurrentPresetIsSaved;
    
    //==============================================================================
    juce::File mCurrentlyLoadedPreset;
    juce::Array<juce::File> mLocalPresets;
    
    //==============================================================================
    juce::String mCurrentPresetName;
    juce::String presetNotes;
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
