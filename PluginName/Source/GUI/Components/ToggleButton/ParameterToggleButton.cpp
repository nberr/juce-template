/*
  ==============================================================================

    ParameterToggleButton.cpp
    Created: 10 Jan 2022 5:58:26pm
    Author:  Nicholas Berriochoa

  ==============================================================================
*/

#include "ParameterToggleButton.h"

//==============================================================================
ParameterToggleButton::ParameterToggleButton(juce::AudioProcessorValueTreeState& stateToControl,
                      const juce::String& parameterID,
                      const juce::String& parameterLabel)
:   juce::TextButton(parameterLabel),
    attachment(stateToControl, parameterID, *this)
{
    setToggleable(true);
    
    // TODO: set toggle state based on parameter state
}

ParameterToggleButton::~ParameterToggleButton()
{
    
}
