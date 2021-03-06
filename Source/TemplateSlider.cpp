/*
  ==============================================================================

    TemplateSlider.cpp
    Created: 6 Mar 2021 7:32:55pm
    Author:  Nicholas Berriochoa

  ==============================================================================
*/

#include "TemplateSlider.h"

#include "InterfaceDefines.h"
#include "TemplateParameters.h"

TemplateSlider::TemplateSlider(juce::AudioProcessorValueTreeState& stateToControl, int paramID)
:   juce::Slider(TemplateParameterID[paramID])
{
    // set the size and location
    // set the range of the slider
    // set the style of the slider
    
    mAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(stateToControl, TemplateParameterID[paramID], *this);
}

TemplateSlider::~TemplateSlider()
{
    
}
