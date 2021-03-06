/*
  ==============================================================================

    TemplateSlider.h
    Created: 6 Mar 2021 7:32:55pm
    Author:  Nicholas Berriochoa

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class TemplateSlider
:   public juce::Slider
{
public:
    TemplateSlider(juce::AudioProcessorValueTreeState& stateToControl, int paramID);
    ~TemplateSlider();
    
private:
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mAttachment;
};
