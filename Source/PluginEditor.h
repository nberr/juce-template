/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

#include "MainPanel.h"
#include "TemplateLookAndFeel.h"

//==============================================================================
/**
*/
class Template_AudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    Template_AudioProcessorEditor (Template_AudioProcessor&);
    ~Template_AudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    Template_AudioProcessor& audioProcessor;
    
    std::unique_ptr<MainPanel> mMainPanel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Template_AudioProcessorEditor)
};
