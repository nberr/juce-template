/*
  ==============================================================================

    ParameterSlider.cpp
    Created: 10 Jan 2022 5:58:47pm
    Author:  Nicholas Berriochoa

  ==============================================================================
*/

#include "ParameterSlider.h"

//==============================================================================
ParameterSlider::ParameterSlider(juce::AudioProcessorValueTreeState& stateToControl,
                                 const juce::String& parameterID,
                                 const juce::String& parameterLabel)
:   juce::Slider(parameterLabel),
    attachment(stateToControl, parameterID, *this)
{
    // TODO: set slider value based on parameter value
}

ParameterSlider::~ParameterSlider()
{
    
}
