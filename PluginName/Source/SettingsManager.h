/*
  ==============================================================================

    SettingsManager.h
    Created: 17 Jan 2022 6:52:58pm
    Author:  Nicholas Berriochoa

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
class SettingsManager
{
public:
    //==============================================================================
    SettingsManager(juce::AudioProcessor* inProcssor, juce::ValueTree* inSettings);
    ~SettingsManager();
    
    //==============================================================================
    void saveSettings();
    void loadSettings();
    
private:
    //==============================================================================
    juce::AudioProcessor* mProcessor;
    
    //==============================================================================
    void createSettingsLayout();
    
    juce::ValueTree *settings;
    juce::String settingsDirectory;
    juce::String settingsXML;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SettingsManager)
};
