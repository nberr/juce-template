/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

#include "MainPanel.h"
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
    
    std::unique_ptr<MainPanel> mMainPanel;
    float* mGUIScale;
    
    juce::PopupMenu menu;

    juce::TextButton small;
    juce::TextButton medium;
    juce::TextButton large;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginNameAudioProcessorEditor)
};
