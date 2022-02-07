/*
  ==============================================================================

    ParameterToggleButton.h
    Created: 10 Jan 2022 5:58:26pm
    Author:  Nicholas Berriochoa

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
class ParameterToggleButton
:   public juce::TextButton
{
public:
    //==============================================================================
    ParameterToggleButton(juce::AudioProcessorValueTreeState& stateToControl,
                          const juce::String& parameterID,
                          const juce::String& parameterLabel);
    ~ParameterToggleButton();
    
private:
    //==============================================================================
    juce::AudioProcessorValueTreeState::ButtonAttachment attachment;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ParameterToggleButton)
};
