/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

// panels
#include "PanelBase.h"
#include "MenuPanel.h"
#include "PresetPanel.h"
#include "MainPanel.h"
#include "SidePanel.h"

// overlays
#include "DisplayPresetsOverlay.h"
#include "SavePresetOverlay.h"
#include "DeletePresetOverlay.h"
#include "UpdatePresetOverlay.h"

// registration
#include "MarketplaceStatus.h"
#include "UnlockForm.h"

#include "ContextMenu.h"

//==============================================================================
/**
*/
class PluginNameAudioProcessorEditor
:   public juce::AudioProcessorEditor,
    private juce::Timer
{
public:
    //==============================================================================
    PluginNameAudioProcessorEditor (PluginNameAudioProcessor&);
    ~PluginNameAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    
    //==============================================================================
    void showForm();

private:
    //==============================================================================
    void timerCallback() override;
    void unlockApp();
    void checkFeature();
    
    //==============================================================================
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    PluginNameAudioProcessor& audioProcessor;
    
    //==============================================================================
    // This template allows two ways to display a UI
    // 1 - pure JUCE; see UI folder for panel hierarchy
    ContextMenu mContextMenu;
    
    // panel hierarchy
    MenuPanel mMenuPanel;
    PresetPanel mPresetPanel;
    MainPanel mMainPanel;
    SidePanel mSidePanel;
    
    //==============================================================================
    std::vector<PanelBase *> panels = {
        &mMenuPanel,
        &mPresetPanel,
        &mMainPanel,
        &mSidePanel
    };
    
    // overlays
    DisplayPresetsOverlay mDisplayPresetOverlay;
    SavePresetOverlay savePresetOverlay;
    DeletePresetOverlay deletePresetOverlay;
    UpdatePresetOverlay updatePresetOverlay;
    
    std::vector<PanelBase *> overlays = {
        &mDisplayPresetOverlay,
        &savePresetOverlay,
        &deletePresetOverlay,
        &updatePresetOverlay
    };
    
    // 2 - react-juce; see jsui/src/index.js
    reactjuce::ReactApplicationRoot appRoot;
    reactjuce::AppHarness appHarness;
    
    //==============================================================================
    juce::TextButton unlockButton { "Unlock" },
                     secretButton { "Super Secret Feature" };

    MarketplaceStatus marketplaceStatus;
    UnlockForm unlockForm;

    bool isUnlocked = false;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginNameAudioProcessorEditor)
};
