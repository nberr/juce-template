/*
  ==============================================================================

    OverlayBase.cpp
    Created: 23 Jan 2022 8:12:54am
    Author:  Nicholas Berriochoa

  ==============================================================================
*/

#include "OverlayBase.h"

//==============================================================================
OverlayBase::OverlayBase(PluginNameAudioProcessor* inProcessor, ContextMenu* inContextMenu)
:   PanelBase(inProcessor, inContextMenu)
{
    setName("OverlayBase");
    setComponentID("OverlayBaseID");
}

OverlayBase::~OverlayBase()
{
    
}

//==============================================================================
void OverlayBase::paint(juce::Graphics& g)
{
    g.setColour(juce::Colours::white.withAlpha(0.5f));
    g.fillAll();
    
    g.setColour(juce::Colours::black);
    g.drawRoundedRectangle(0, 0, getWidth(), getHeight(), PluginNameGUI::corner_size, PluginNameGUI::line_thickness);
}

//==============================================================================
void OverlayBase::mouseDown(const juce::MouseEvent& event)
{
    
}
