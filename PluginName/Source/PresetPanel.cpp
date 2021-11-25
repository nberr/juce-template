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
    
    mPresetMenu.setButtonText("Current Preset"); // set the text to the current preset
    mPresetMenu.setName("PresetMenu");
    mPresetMenu.setTriggeredOnMouseDown(true);
    mPresetMenu.addListener(this);
    //addAndMakeVisible(&mPresetMenu);
    
    mPrevPreset.setButtonText("<");
    mPrevPreset.setName("PrevPreset");
    mPrevPreset.setTriggeredOnMouseDown(true);
    mPrevPreset.addListener(this);
    //addAndMakeVisible(&mPrevPreset);
    
    mNextPreset.setButtonText(">");
    mNextPreset.setName("NextPreset");
    mNextPreset.setTriggeredOnMouseDown(true);
    mNextPreset.addListener(this);
    //addAndMakeVisible(&mNextPreset);
    
    mPresetA.setButtonText("A");
    mPresetA.setName("PresetA");
    mPresetA.setTriggeredOnMouseDown(true);
    mPresetA.addListener(this);
    addAndMakeVisible(&mPresetA);
    
    mPresetB.setButtonText("B");
    mPresetB.setName("PresetB");
    mPresetB.setTriggeredOnMouseDown(true);
    mPresetB.addListener(this);
    addAndMakeVisible(&mPresetB);
    
    mPresetCopy.setButtonText("->"); // set arrow based on if A or B is selected
    mPresetCopy.setName("PresetCopy");
    mPresetCopy.setTriggeredOnMouseDown(true);
    mPresetCopy.addListener(this);
    addAndMakeVisible(&mPresetCopy);
}

PresetPanel::~PresetPanel()
{
    
}

void PresetPanel::resized()
{
    float scale = *mContextMenu->mGUIScale;
    
    mPresetMenu.setSize(PresetPanelGUI::preset_display_width * scale, PresetPanelGUI::preset_display_height * scale);
    mPresetMenu.setCentrePosition(PresetPanelGUI::width * scale * 0.5f, PresetPanelGUI::height * scale * 0.5f);
    
    
    mPrevPreset.setBounds(mPresetMenu.getX() - (PresetPanelGUI::change_preset_width*scale),
                          mPresetMenu.getY(),
                          PresetPanelGUI::change_preset_width * scale,
                          PresetPanelGUI::change_preset_height * scale);
    
    mNextPreset.setBounds(mPresetMenu.getX() + mPresetMenu.getWidth(),
                          mPresetMenu.getY(),
                          PresetPanelGUI::change_preset_width * scale,
                          PresetPanelGUI::change_preset_height * scale);
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
        if (b == &mPrevPreset)
        {
            
        }
        else if (b == &mNextPreset)
        {
            
        }
        else if (b == &mPresetMenu)
        {
            // toggle overlay
            getParentComponent()->findChildWithID("PresetOverlayID")->setVisible(true);
        }
    }
}
