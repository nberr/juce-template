/*
  ==============================================================================

    PresetViewItem.cpp
    Created: 21 Jan 2022 12:31:53pm
    Author:  Nicholas Berriochoa

  ==============================================================================
*/

#include "PresetViewItem.h"

//==============================================================================
PresetViewItem::PresetViewItem(juce::String name, juce::String notes, bool isDefault)
{
    this->name = name;
    this->notes = notes;
    this->isDefault = isDefault;
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
    juce::String text = name;
    
    if (name.endsWith(".xml")) {
        text = name.substring(0, name.length() - 4);
    }
    
    if (notes.isNotEmpty()) {
        text = text + " - " + notes;
    }
    
    g.fillAll(juce::Colours::grey);
    g.setColour(juce::Colours::black);
    g.drawText(text , 5, 0, width, height, juce::Justification::left);
}
