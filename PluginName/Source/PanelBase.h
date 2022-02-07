/*
  ==============================================================================

    PanelBase.h
    Created: 25 Nov 2021 8:55:47am
    Author:  Nicholas Berriochoa

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#include "PluginNameGUI.h"
#include "PluginNameLookAndFeel.h"
#include "PluginProcessor.h"
#include "ContextMenu.h"
#include "PluginNameSettings.h"

//==============================================================================
class PanelBase
:   public juce::Component
{
public:
    //==============================================================================
    PanelBase(PluginNameAudioProcessor* processor, ContextMenu* contextMenu);
    ~PanelBase();
    
    //==============================================================================
    void paint(juce::Graphics& g) override;
    
    //==============================================================================
    void mouseDown(const juce::MouseEvent& event) override;
    
protected:
    //==============================================================================
    PluginNameAudioProcessor *processor;
    ContextMenu *contextMenu;
    
    //==============================================================================
    juce::ValueTree guiScale;
};
