/*
  ==============================================================================

    MainPanel.h
    Created: 12 Apr 2021 5:03:39pm
    Author:  Nicholas Berriochoa

  ==============================================================================
*/

#pragma once

#include "PanelBase.h"

#include "PluginNameMarketplaceStatus.h"
#include "PluginNameUnlockForm.h"

#include "PresetPanel.h"
#include "PresetOverlay.h"
#include "SavePresetOverlay.h"

class MainPanel
:   public PanelBase,
    private juce::Timer
{
public:
    MainPanel(PluginNameAudioProcessor* inProcessor, ContextMenu* inContextMenu);
    ~MainPanel();
    
    void resized() override;
private:    
    void timerCallback() override;
    void showForm();
    void unlockApp();
    void checkFeature();
    
    PresetPanel mPresetPanel;
    PresetOverlay mPresetOverlay;
    SavePresetOverlay mSavePresetOverlay;
    
    juce::Label      unlockLabel  { {}, "Status: Locked" };
    juce::TextButton unlockButton { "Unlock" },
                     secretButton { "Super Secret Feature" };

    PluginNameMarketplaceStatus marketplaceStatus;
    PluginNameUnlockForm unlockForm;

    bool isUnlocked = false;
    
    
    
};
