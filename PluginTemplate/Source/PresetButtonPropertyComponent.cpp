/*
  ==============================================================================

    PresetButtonPropertyComponent.cpp
    Created: 16 Jun 2021 11:27:17pm
    Author:  Nicholas Berriochoa

  ==============================================================================
*/

#include "PresetButtonPropertyComponent.h"

PresetButtonPropertyComponent::PresetButtonPropertyComponent(juce::String propertyName)
:   juce::ButtonPropertyComponent(propertyName, true)
{
    
}

PresetButtonPropertyComponent::~PresetButtonPropertyComponent()
{
    
}

void PresetButtonPropertyComponent::buttonClicked()
{
    
}

juce::String PresetButtonPropertyComponent::getButtonText() const
{
    return "test";
}
