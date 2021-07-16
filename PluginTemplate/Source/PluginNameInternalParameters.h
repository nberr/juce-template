/*
  ==============================================================================

    PluginNameInternalParameters.h
    Created: 6 Jun 2021 3:45:27pm
    Author:  Nicholas Berriochoa

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#if JUCE_WINDOWS
    #define DIR_SEP "\\"
#elseif JUCE_MAC
    #define DIR_SEP "/"
#else
    #define DIR_SEP "/"
#endif

class PluginNameInternalParameters {
public:
    PluginNameInternalParameters()
    {
        const juce::String musicFolder = "Music";
        const juce::String presetPathFromHome = DIR_SEP + musicFolder + DIR_SEP + JucePlugin_Manufacturer + DIR_SEP + JucePlugin_Name;
        mPresetPath = juce::File::getSpecialLocation(juce::File::userHomeDirectory).getFullPathName() + presetPathFromHome;
    }
    ~PluginNameInternalParameters()
    {
        
    }
    
    juce::String mPresetPath;
    
    float mGUIScale = 1;
    int mDefaultPreset = 0;
    
    
private:
    
};
