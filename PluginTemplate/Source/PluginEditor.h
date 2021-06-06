/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

#include "MainPanel.h"
#include "ContextMenu.h"
#include "PluginNameInternalParameters.h"

//==============================================================================
/**
*/
class PluginNameAudioProcessorEditor  : public juce::AudioProcessorEditor
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
    ContextMenu mContextMenu;
    
    
    std::unique_ptr<MainPanel> mMainPanel;
    float* mGUIScale;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginNameAudioProcessorEditor)
};
