/*
  ==============================================================================

    PanelBase.h
    Created: 25 Nov 2021 8:55:47am
    Author:  Nicholas Berriochoa

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#include "InterfaceDefines.h"
#include "PluginNameLookAndFeel.h"
#include "PluginProcessor.h"
#include "ContextMenu.h"
#include "PluginNameInternalParameters.h"

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
