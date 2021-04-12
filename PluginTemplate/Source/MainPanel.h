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

class MainPanel
:   public PanelBase,
    private juce::Timer
{
public:
    MainPanel(PluginNameAudioProcessor* inProcessor);
    ~MainPanel();
private:
    void timerCallback() override;
    void showForm();
    void unlockApp();
    void checkFeature();
    
    juce::Label      unlockLabel  { {}, "Status: Locked" };
    juce::TextButton unlockButton { "Unlock" },
                     secretButton { "Super Secret Feature" };

    PluginNameMarketplaceStatus marketplaceStatus;
    PluginNameUnlockForm unlockForm;

    bool isUnlocked = false;
    
    std::unique_ptr<PresetPanel> mPresetPanel;
};
