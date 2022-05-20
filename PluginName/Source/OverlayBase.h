/*
  ==============================================================================

    OverlayBase.h
    Created: 23 Jan 2022 8:12:54am
    Author:  Nicholas Berriochoa

  ==============================================================================
*/

#pragma once

#include "PanelBase.h"

//==============================================================================
class OverlayBase
:   public PanelBase
{
public:
    //==============================================================================
    OverlayBase(PluginNameAudioProcessor* inProcessor, ContextMenu* inContextMenu);
    ~OverlayBase() override;
    
    //==============================================================================
    void paint(juce::Graphics& g) override;
    
    //==============================================================================
    void mouseDown(const juce::MouseEvent& event) override;
    
};
