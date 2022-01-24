/*
  ==============================================================================

    PresetViewItem.cpp
    Created: 21 Jan 2022 12:31:53pm
    Author:  Nicholas Berriochoa

  ==============================================================================
*/

#include "PresetViewItem.h"

//==============================================================================
PresetViewItem::PresetViewItem(juce::String inName, juce::String inNotes, bool inIsDefault, bool inIsDirectory)
{
    name = inName;
    notes = inNotes;
    isDefault = inIsDefault;
    isDirectory = inIsDirectory;
    //addSubItem(new PresetViewItem(level));
}

PresetViewItem::~PresetViewItem()
{
    
}

bool PresetViewItem::mightContainSubItems()
{
    return getNumSubItems() != 0;
}

void PresetViewItem::paintItem(juce::Graphics& g, int width, int height)
{
    g.fillAll(juce::Colours::grey);
    g.setColour(juce::Colours::black);
    g.drawText("item", 0, 0, width, height, juce::Justification::left);
}
