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

#include "ParameterComboBox.h"
#include "ParameterSlider.h"
#include "ParameterToggleButton.h"

//==============================================================================
class MainPanel
:   public PanelBase,
    public juce::Button::Listener,
    public juce::Slider::Listener,
    public juce::ComboBox::Listener
{
public:
    //==============================================================================
    MainPanel(PluginNameAudioProcessor* processor, ContextMenu* contextMenu);
    ~MainPanel();
    
    //==============================================================================
    void resized() override;
    
    //==============================================================================
    void buttonClicked(juce::Button* b) override;
    void sliderValueChanged(juce::Slider* s) override;
    void comboBoxChanged(juce::ComboBox* cb) override;
    
private:
    //==============================================================================
    ParameterComboBox pChoice;
    ParameterSlider pInt;
    ParameterSlider pFloat;
    ParameterToggleButton pBool;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainPanel)
};
