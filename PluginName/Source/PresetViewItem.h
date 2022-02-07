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
    PresetViewItem(juce::String name, juce::String notes, bool isDefault, bool isDirectory);
    ~PresetViewItem();
    
    //==============================================================================
    bool mightContainSubItems() override;
    void paintItem(juce::Graphics& g, int width, int height) override;
    
    //==============================================================================
    bool isDirectory = false;
    
private:
    //==============================================================================
    juce::String name;
    juce::String notes;
    juce::String path;
    
    bool isDefault = false;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PresetViewItem)
};
