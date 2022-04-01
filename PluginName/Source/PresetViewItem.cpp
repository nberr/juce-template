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

#include "ContextMenu.h"

//==============================================================================
PresetViewItem::PresetViewItem(juce::String name, juce::String notes, bool isDefault, bool isDirectory, bool isUserPreset)
{
    this->fileName = name;
    this->notes = notes;
    this->isDefault = isDefault;
    this->isDirectory = isDirectory;
    this->isUserPreset = isUserPreset;
    
    // set the display name
    // remove the ".xml" at the end if it's not a directory
    displayName = (fileName.endsWith(".xml")) ? fileName.substring(0, fileName.length() - 4) : fileName;
    
    // add notes to the end of the displayName if there are any
    display = (notes.isNotEmpty()) ? displayName + " - " + notes : displayName;
    
    // set the initial paint type
    if (isDirectory) {
        paintType = PaintType::Directory;
    }
    else {
        paintType = PaintType::UnselectedPreset;
    }
}

PresetViewItem::~PresetViewItem()
{

}

//==============================================================================
bool PresetViewItem::mightContainSubItems()
{
    return getNumSubItems() != 0;
}

void PresetViewItem::paintItem(juce::Graphics& g, int width, int height)
{
    switch(paintType) {
        case PaintType::Directory:
            g.fillAll(juce::Colours::blue.withAlpha (0.4f));
            break;
        case PaintType::SelectedPreset:
            g.fillAll(juce::Colours::blue.withAlpha (0.3f));
            break;
        case PaintType::UnselectedPreset:
            g.fillAll(juce::Colours::blue.withAlpha (0.1f));
            break;
    }
    
    g.setColour(juce::Colours::black);
    g.drawText(display + ((isDefault) ? " default" : ""), 5, 0, width, height, juce::Justification::left);
}

void PresetViewItem::itemClicked(const juce::MouseEvent& m)
{
    // ignore if the item is a directory
    if (isDirectory) {
        setOpen(!isOpen());
        return;
    }
    
    bool rightClick = juce::ModifierKeys::getCurrentModifiers().isPopupMenu();
    
    PresetDisplayOverlay *overlay = (PresetDisplayOverlay *)getOwnerView()->getParentComponent()->getParentComponent();
    PresetPanel *panel = (PresetPanel *)overlay->getParentComponent()->findChildWithID("PresetPanelID");
    
    auto pm = overlay->getPresetManager();
    
    if (rightClick) {
        overlay->showContextMenu(displayName, isUserPreset);
    }
    else {
        // talk to the preset manager
        pm->loadPreset(fileName);
        panel->setPresetMenu(displayName);
        
        pm->loadPreset(displayName);
    }
}

bool PresetViewItem::canBeSelected() const
{
    return !isDirectory;
}

void PresetViewItem::itemSelectionChanged(bool isNowSelected)
{
    bool rightClick = juce::ModifierKeys::getCurrentModifiers().isPopupMenu();
    
    if (isNowSelected) {
        // currently selected item
        if (rightClick) {
            // paint like a normal unselected item
            paintType = PaintType::UnselectedPreset;
        }
        else {
            // paint like the item is selected
            paintType = PaintType::SelectedPreset;
        }
    }
    else {
        // previously selected item
        if (rightClick) {
            // paint like the item is selected
            paintType = PaintType::SelectedPreset;
        }
        else {
            // paint like an normal unselected item
            paintType = PaintType::UnselectedPreset;
        }
    }
}

//==============================================================================
juce::String PresetViewItem::getDisplayName()
{
    return displayName;
}
