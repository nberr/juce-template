/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

// panels
#include "MenuPanel.h"
#include "PresetPanel.h"
#include "PresetOverlay.h"
#include "MainPanel.h"
#include "SidePanel.h"

#include "PluginNameMarketplaceStatus.h"
#include "PluginNameUnlockForm.h"

#include "ContextMenu.h"
#include "PluginNameParameters.h"

//==============================================================================
/**
*/
class PluginNameAudioProcessorEditor
:   public juce::AudioProcessorEditor,
    private juce::Timer
{
public:
    PluginNameAudioProcessorEditor (PluginNameAudioProcessor&);
    ~PluginNameAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    PluginNameAudioProcessor& audioProcessor;
    
    // This template allows two ways to display a UI
    // 1 - pure JUCE; see UI folder for panel hierarchy
    ContextMenu mContextMenu;
    
    // panel hierarchy
    MenuPanel mMenuPanel;
    PresetPanel mPresetPanel;
    PresetOverlay mPresetOverlay;
    MainPanel mMainPanel;
    SidePanel mSidePanel;
    
    // 2 - react-juce; see jsui/src/index.js
    reactjuce::ReactApplicationRoot appRoot;
    reactjuce::AppHarness appHarness;
    
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

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginNameAudioProcessorEditor)
};
