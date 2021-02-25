/*
  ==============================================================================

    TemplatePresetPanel.h
    Created: 25 Feb 2021 4:08:23pm
    Author:  Nicholas Berriochoa

  ==============================================================================
*/

#pragma once

#include "PanelBase.h"

class PresetPanel
:   public PanelBase,
    public juce::Button::Listener,
    public juce::ComboBox::Listener
{
public:
    PresetPanel(Template_AudioProcessor *inProcessor);
    ~PresetPanel();
    
    void paint(juce::Graphics& g) override;
        
    void buttonClicked(juce::Button*) override;
    void comboBoxChanged(juce::ComboBox* comboBoxThatHasChanged) override;
private:
    void displaySaveAsPopup();
        
    void updatePresetComboBox();
        
    std::unique_ptr<juce::ComboBox> mPresetDisplay;
        
    std::unique_ptr<juce::TextButton> mNewPreset, mSavePreset, mSaveAsPreset;
};
