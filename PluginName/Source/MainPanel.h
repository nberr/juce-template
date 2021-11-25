/*
  ==============================================================================

    MainPanel.h
    Created: 25 Nov 2021 8:56:29am
    Author:  Nicholas Berriochoa

  ==============================================================================
*/

#pragma once

#include "PanelBase.h"

#include "PluginNameMarketplaceStatus.h"
#include "PluginNameUnlockForm.h"

#include "PresetPanel.h"
#include "PresetOverlay.h"

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
    
    reactjuce::ReactApplicationRoot appRoot;
    reactjuce::AppHarness appHarness;

    juce::Label      unlockLabel  { {}, "Status: Locked" };
    juce::TextButton unlockButton { "Unlock" },
                     secretButton { "Super Secret Feature" };

    PluginNameMarketplaceStatus marketplaceStatus;
    PluginNameUnlockForm unlockForm;

    bool isUnlocked = false;
    
    PresetPanel mPresetPanel;
    PresetOverlay mPresetOverlay;
};
