/*
  ==============================================================================

    PresetViewItem.cpp
    Created: 21 Jan 2022 12:31:53pm
    Author:  Nicholas Berriochoa

  ==============================================================================
*/

#include "PresetViewItem.h"

#include "PresetPanel.h"
#include "PresetDisplayOverlay.h"

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
    
    // remove the .xml at the end
    if (name.endsWith(".xml")) {
        text = name.substring(0, name.length() - 4);
    }
    
    // append notes if there are any
    if (notes.isNotEmpty()) {
        text = text + " - " + notes;
    }
    
    // paint the display
    // TODO: adjust this to look better
    g.fillAll(juce::Colours::grey);
    g.setColour(juce::Colours::black);
    g.drawText(text , 5, 0, width, height, juce::Justification::left);
}

void PresetViewItem::itemClicked(const juce::MouseEvent& m)
{
    bool rightClick = juce::ModifierKeys::getCurrentModifiers().isPopupMenu();
    
    if (rightClick) {
        // TODO: show the context menu on right click
    }
    else {
        // talk to the preset manager
        PresetDisplayOverlay *overlay = (PresetDisplayOverlay *)getOwnerView()->getParentComponent()->getParentComponent();
        PresetPanel *panel = (PresetPanel *)overlay->getParentComponent()->findChildWithID("PresetPanelID");
        
        auto pm = overlay->getPresetManager();
        
        pm->loadPreset(name);
        panel->setPresetMenu(name);
    }
}
