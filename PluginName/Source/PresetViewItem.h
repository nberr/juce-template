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
    PresetViewItem(juce::String name, juce::String notes, bool isDefault, bool isDirectory, bool isUserPreset);
    ~PresetViewItem();
    
    //==============================================================================
    bool mightContainSubItems() override;
    void paintItem(juce::Graphics& g, int width, int height) override;
    void itemClicked(const juce::MouseEvent& m) override;
    bool canBeSelected() const override;
    
    //==============================================================================
    juce::String getDisplayName();
    
private:
    //==============================================================================
    juce::String fileName, displayName, display, notes;
    bool isDefault = false, isDirectory, isUserPreset;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PresetViewItem)
};
