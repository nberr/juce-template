/*
  ==============================================================================

    PluginNameMessage.cpp
    Created: 9 Apr 2022 10:34:57pm
    Author:  Nicholas Berriochoa

  ==============================================================================
*/

#include "PluginNameMessage.h"

#include "PluginNameMessages.h"

//==============================================================================
PluginNameMessage::PluginNameMessage(juce::String message)
{
    juce::StringArray tokens;
    tokens.addTokens(message, " ", "");
    
    if (tokens.size() < 2) {
        validity = false;
        return;
    }
    
    if (tokens[0] != "PluginName") {
        validity = false;
    }
    
    command = tokens[1];
    if (PluginNameMessages::ValidMessages.contains(command) == false) {
        validity = false;
    }
    
    if (tokens.size() > 2) {
        for (int i = 2; i < tokens.size(); i++) {
            values.add(tokens[i]);
        }
    }
}

PluginNameMessage::~PluginNameMessage()
{
    
}

//==============================================================================
bool PluginNameMessage::isValid()
{
    return validity;
}

//==============================================================================
juce::String PluginNameMessage::getCommand()
{
    return command;
}

juce::StringArray PluginNameMessage::getValues()
{
    return values;
}
