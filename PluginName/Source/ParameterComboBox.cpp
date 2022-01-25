/*
  ==============================================================================

    ParameterComboBox.cpp
    Created: 10 Jan 2022 5:58:35pm
    Author:  Nicholas Berriochoa

  ==============================================================================
*/

#include "ParameterComboBox.h"

//==============================================================================
ParameterComboBox::ParameterComboBox(juce::AudioProcessorValueTreeState& stateToControl, const juce::String& parameterID)
:   juce::ComboBox(parameterID),
    attachment(stateToControl, parameterID, *this)
{
    setSelectedId(1, juce::NotificationType::dontSendNotification);
}

ParameterComboBox::~ParameterComboBox()
{
    
}
