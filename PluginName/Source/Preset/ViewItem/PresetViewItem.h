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
    PresetViewItem(juce::String inName, juce::String inNotes, bool inIsDefault, bool inIsDirectory, bool inIsUserPreset);
    ~PresetViewItem() override;
    
    //==============================================================================
    bool mightContainSubItems() override;
    void paintItem(juce::Graphics& g, int width, int height) override;
    void itemClicked(const juce::MouseEvent& m) override;
    bool canBeSelected() const override;
    void itemSelectionChanged(bool isNowSelected) override;
    
    //==============================================================================
    juce::String getDisplayName();
    
    enum PaintType {
        Directory = 0,
        SelectedPreset,
        UnselectedPreset
    };
    
private:
    //==============================================================================
    juce::String fileName, displayName, display, notes;
    PaintType paintType;
    bool isDefault = false, isDirectory, isUserPreset;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PresetViewItem)
};
