/*
  ==============================================================================

    PresetButtonPropertyComponent.h
    Created: 16 Jun 2021 11:27:17pm
    Author:  Nicholas Berriochoa

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class PresetButtonPropertyComponent
:   public juce::ButtonPropertyComponent
{
public:
    PresetButtonPropertyComponent(juce::String propertyName);
    ~PresetButtonPropertyComponent();
    
    void buttonClicked() override;
    juce::String getButtonText() const override;
    
private:
    
};
