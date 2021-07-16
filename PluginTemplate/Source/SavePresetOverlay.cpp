/*
  ==============================================================================

    SavePresetOverlay.cpp
    Created: 18 Jun 2021 8:14:40pm
    Author:  Nicholas Berriochoa

  ==============================================================================
*/

#include "SavePresetOverlay.h"

SavePresetOverlay::SavePresetOverlay(PluginNameAudioProcessor* inProcessor, ContextMenu* inContextMenu)
:   PanelBase(inProcessor, inContextMenu),
    mPresetNameLabel("PresetNameLabel", "Preset Name:"),
    mSavePreset("Save"),
    mCancel("Cancel")
{
    setName("SavePresetOverlay");
    setComponentID("SavePresetOverlayID");
    setOpaque(true);
    
    
    mPresetNameLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::black);
    addAndMakeVisible(&mPresetNameLabel);
    
    addAndMakeVisible(&mPresetNameInput);
    
    mSavePreset.addListener(this);
    addAndMakeVisible(&mSavePreset);
    
    mCancel.addListener(this);
    addAndMakeVisible(&mCancel);
    
    
}

SavePresetOverlay::~SavePresetOverlay()
{
    
}

void SavePresetOverlay::resized()
{
    float scale = *mContextMenu->mGUIScale;
    
    mPresetNameLabel.setBounds(20, 100, 100, 20);
    mPresetNameInput.setBounds(300, 300, 200, 20);
    
    mSavePreset.setBounds(0, 0, 100, 50);
    mCancel.setBounds(0, 50, 100, 50);
}

void SavePresetOverlay::buttonClicked(juce::Button* b)
{
    if (b == &mSavePreset) {
        mProcessor->getPresetManager()->saveAsPreset(mPresetNameInput.getText());
        mPresetNameInput.clear();
        setVisible(false);
    }
    else if (b == &mCancel) {
        setVisible(false);
    }
}
