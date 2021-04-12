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

class PanelBase
:   public juce::Component
{
public:
    PanelBase(PluginNameAudioProcessor* inProcessor);
    ~PanelBase();
    
    void paint(juce::Graphics& g) override;
protected:
    PluginNameAudioProcessor *mProcessor;
};
