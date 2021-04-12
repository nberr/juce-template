/*
  ==============================================================================

    PanelBase.cpp
    Created: 12 Apr 2021 5:02:48pm
    Author:  Nicholas Berriochoa

  ==============================================================================
*/

#include "PanelBase.h"

PanelBase::PanelBase(PluginNameAudioProcessor *inProcessor)
{
    mProcessor = inProcessor;
}

PanelBase::~PanelBase()
{
    
}

void PanelBase::paint(juce::Graphics& g)
{
    g.setColour(juce::Colours::white);
    g.fillAll();
    
    g.setColour(juce::Colours::black);
    g.drawRoundedRectangle(0, 0, getWidth(), getHeight(), CORNER_SIZE, LINE_THICKNESS);
}
