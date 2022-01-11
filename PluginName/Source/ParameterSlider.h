/*
  ==============================================================================

    ParameterSlider.h
    Created: 10 Jan 2022 5:58:47pm
    Author:  Nicholas Berriochoa

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class ParameterSlider
:   public juce::Slider
{
public:
    ParameterSlider(juce::AudioProcessorValueTreeState& stateToControl,
                    const juce::String& parameterID,
                    const juce::String& parameterLabel);
    ~ParameterSlider();
private:
    juce::AudioProcessorValueTreeState::SliderAttachment attachment;
};
