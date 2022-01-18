/*
  ==============================================================================

    PresetManager.h
    Created: 25 Nov 2021 9:02:19am
    Author:  Nicholas Berriochoa

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#define PRESET_FILE_EXTENSION ".xml"

//==============================================================================
class PresetManager
{
public:
    //==============================================================================
    PresetManager(juce::AudioProcessor* inProcssor);
    ~PresetManager();
    
    //==============================================================================
    void getXmlForPreset(juce::XmlElement* inElement);
    void loadPresetForXml(juce::XmlElement* inElement);
    
    //==============================================================================
    int getNumberOfPresets();
    juce::String getPresetName(int inPresetIndex);
    
    //==============================================================================
    void createNewPreset();
    void savePreset();
    void saveAsPreset(juce::String inPresetName);
    void loadPreset(int inPresetIndex);
    
    //==============================================================================
    bool getIsCurrentPresetSaved();
    juce::String getCurrentPresetName();
    
private:
    //==============================================================================
    void storeLocalPreset();
    
    //==============================================================================
    bool mCurrentPresetIsSaved;
    
    //==============================================================================
    juce::File mCurrentlyLoadedPreset;
    juce::Array<juce::File> mLocalPresets;
    
    //==============================================================================
    juce::String mCurrentPresetName;
    juce::String mPresetDirectory;
    
    //==============================================================================
    juce::AudioProcessor* mProcessor;
    
    //==============================================================================
    juce::XmlElement* mCurrentPresetXml;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PresetManager)
};
