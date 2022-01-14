/*
  ==============================================================================

    MainPanel.h
    Created: 25 Nov 2021 8:56:29am
    Author:  Nicholas Berriochoa

  ==============================================================================
*/

#pragma once

#include "PanelBase.h"

#include "PresetPanel.h"
#include "PresetOverlay.h"

#include "ParameterComboBox.h"
#include "ParameterSlider.h"
#include "ParameterToggleButton.h"

//==============================================================================
class MainPanel
:   public PanelBase
{
public:
    //==============================================================================
    MainPanel(PluginNameAudioProcessor* inProcessor, ContextMenu* inContextMenu);
    ~MainPanel();
    
    //==============================================================================
    void resized() override;
    
private:
    //==============================================================================
    ParameterComboBox pChoice;
    ParameterSlider pInt;
    ParameterSlider pFloat;
    ParameterToggleButton pBool;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainPanel)
};
