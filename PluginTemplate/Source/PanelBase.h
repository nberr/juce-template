/*
  ==============================================================================

    PanelBase.h
    Created: 12 Apr 2021 5:02:48pm
    Author:  Nicholas Berriochoa

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#include "InterfaceDefines.h"
#include "PluginNameLookAndFeel.h"
#include "PluginProcessor.h"
#include "ContextMenu.h"

class PanelBase
:   public juce::Component
{
public:
    PanelBase(PluginNameAudioProcessor* inProcessor, ContextMenu* inContextMenu);
    ~PanelBase();
    
    void paint(juce::Graphics& g) override;
    void mouseDown(const juce::MouseEvent& event) override;
    
protected:
    PluginNameAudioProcessor *mProcessor;
    ContextMenu *mContextMenu;
};
