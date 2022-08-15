/*
  ==============================================================================

    SidePanel.h
    Created: 25 Nov 2021 8:56:43am
    Author:  Nicholas Berriochoa

  ==============================================================================
*/

#pragma once

#include "PanelBase.h"

//==============================================================================
class SidePanel
:   public PanelBase
{
public:
    //==============================================================================
    SidePanel(PluginNameAudioProcessor* inProcessor, ContextMenu* inContextMenu);
    ~SidePanel() override;
    
    //==============================================================================
    void resized() override;
    
private:
    //==============================================================================
    juce::TextButton b {"button"};
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SidePanel)
};
