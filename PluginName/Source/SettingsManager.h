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
    SettingsManager(juce::AudioProcessor* inProcssor);
    ~SettingsManager();
    
    //==============================================================================
    void saveSettings();
    
private:
    //==============================================================================
    juce::AudioProcessor* mProcessor;
    
    //==============================================================================
    juce::ValueTree settings;
    juce::String settingsDirectory;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SettingsManager)
};
