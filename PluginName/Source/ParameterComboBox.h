/*
  ==============================================================================

    ParameterComboBox.h
    Created: 10 Jan 2022 5:58:35pm
    Author:  Nicholas Berriochoa

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
class ParameterComboBox
:   public juce::ComboBox
{
public:
    //==============================================================================
    ParameterComboBox(juce::AudioProcessorValueTreeState& stateToControl, const juce::String& parameterID);
    ~ParameterComboBox();
    
private:
    //==============================================================================
    juce::AudioProcessorValueTreeState::ComboBoxAttachment attachment;
    
    //==============================================================================
};
