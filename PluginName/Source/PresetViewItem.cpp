/*
  ==============================================================================

    PresetViewItem.cpp
    Created: 21 Jan 2022 12:31:53pm
    Author:  Nicholas Berriochoa

  ==============================================================================
*/

#include "PresetViewItem.h"

//==============================================================================
PresetViewItem::PresetViewItem(juce::String name, juce::String notes, bool isDefault, bool isDirectory)
{
    this->name = name;
    this->notes = notes;
    this->isDefault = isDefault;
    this->isDirectory = isDirectory;
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
    g.drawText(name, 5, 0, width, height, juce::Justification::left);
}
