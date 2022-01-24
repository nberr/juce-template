/*
  ==============================================================================

    PresetViewItem.h
    Created: 21 Jan 2022 12:31:53pm
    Author:  Nicholas Berriochoa

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
class PresetViewItem
:   public juce::TreeViewItem
{
public:
    //==============================================================================
    PresetViewItem(juce::String inName, juce::String inNotes, bool inIsDefault, bool inIsDirectory);
    ~PresetViewItem();
    
    bool mightContainSubItems() override;
    void paintItem(juce::Graphics& g, int width, int height) override;
    
private:
    //==============================================================================
    juce::String name;
    juce::String notes;
    
    bool isDefault = false;
    bool isDirectory = false;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PresetViewItem)
};
