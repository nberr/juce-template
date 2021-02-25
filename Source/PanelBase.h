/*
  ==============================================================================

    PanelBase.h
    Created: 21 Feb 2021 6:50:45pm
    Author:  Nicholas Berriochoa

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#include "InterfaceDefines.h"
#include "TemplateLookAndFeel.h"
#include "PluginProcessor.h"

class PanelBase
:   public juce::Component
{
public:
    PanelBase(Template_AudioProcessor* inProcessor);
    ~PanelBase();
    
    void paint(juce::Graphics& g) override;
protected:
    Template_AudioProcessor *mProcessor;
};
