/*
  ==============================================================================

    PresetPanel.cpp
    Created: 25 Nov 2021 8:56:36am
    Author:  Nicholas Berriochoa

  ==============================================================================
*/

#include "PresetPanel.h"

PresetPanel::PresetPanel(PluginNameAudioProcessor* inProcessor, ContextMenu* inContextMenu)
:   PanelBase(inProcessor, inContextMenu)
{
    setSize(PresetPanelGUI::width * *mContextMenu->mGUIScale, PresetPanelGUI::height * *mContextMenu->mGUIScale);
    setName("PresetPanel");
    setComponentID("PresetPanelID");
    
    // TODO: set the text to the current preset
    presetMenu.setName("PresetMenu");
    presetMenu.setTriggeredOnMouseDown(true);
    presetMenu.addListener(this);
    addAndMakeVisible(presetMenu);
    
    prevPreset.setName("PrevPreset");
    prevPreset.setTriggeredOnMouseDown(true);
    prevPreset.addListener(this);
    addAndMakeVisible(prevPreset);
    
    nextPreset.setName("NextPreset");
    nextPreset.setTriggeredOnMouseDown(true);
    nextPreset.addListener(this);
    addAndMakeVisible(nextPreset);
    
    presetA.setName("PresetA");
    presetA.setTriggeredOnMouseDown(true);
    presetA.addListener(this);
    addAndMakeVisible(presetA);
    
    presetB.setName("PresetB");
    presetB.setTriggeredOnMouseDown(true);
    presetB.addListener(this);
    addAndMakeVisible(presetB);
    
    // TODO: set arrow based on if A or B is selected
    presetCopy.setName("PresetCopy");
    presetCopy.setTriggeredOnMouseDown(true);
    presetCopy.addListener(this);
    addAndMakeVisible(presetCopy);
}

PresetPanel::~PresetPanel()
{
    
}

void PresetPanel::resized()
{
    float scale = PluginNameInternalParameters::GUIScale;
    
    // undo, redo
    
    // prev, menu, next
    
    // A, copy, B
}

void PresetPanel::buttonClicked(juce::Button* b)
{
    bool rightClick = juce::ModifierKeys::getCurrentModifiers().isPopupMenu();
    
    if (rightClick) {
        mContextMenu->showMenu(b->getName());
        auto editor = findParentComponentOfClass<juce::AudioProcessorEditor>();
        editor->resized();
        resized();
    }
    else {
        if (b == &prevPreset)
        {
            
        }
        else if (b == &nextPreset)
        {
            
        }
        else if (b == &presetMenu)
        {
            // toggle overlay
            getParentComponent()->findChildWithID("PresetOverlayID")->setVisible(true);
        }
    }
}
