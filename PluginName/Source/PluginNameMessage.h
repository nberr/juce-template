/*
  ==============================================================================

    PluginNameMessage.h
    Created: 9 Apr 2022 10:34:57pm
    Author:  Nicholas Berriochoa

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
class PluginNameMessage
{
public:
    //==============================================================================
    PluginNameMessage(juce::String message);
    ~PluginNameMessage();
    
    //==============================================================================
    bool isValid();
    
    //==============================================================================
    juce::String getCommand();
    juce::StringArray getValues();
    
private:
    //==============================================================================
    juce::String command;
    juce::StringArray values;
    bool validity = true;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginNameMessage)
};
