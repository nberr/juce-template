/*
  ==============================================================================

    PanelBase.cpp
    Created: 25 Nov 2021 8:55:47am
    Author:  Nicholas Berriochoa

  ==============================================================================
*/

#include "PanelBase.h"

//==============================================================================
PanelBase::PanelBase(PluginNameAudioProcessor* processor, ContextMenu* contextMenu)
{
    setName("PanelBase");
    setComponentID("PanelBaseID");
    
    this->processor = processor;
    this->contextMenu = contextMenu;
    
    guiScale = processor->settings.getChild(PluginNameSettings::PNS_GUIScale);
}

PanelBase::~PanelBase()
{
    
}

//==============================================================================
void PanelBase::paint(juce::Graphics& g)
{
    g.setColour(juce::Colours::white);
    g.fillAll();
    
    g.setColour(juce::Colours::black);
    g.drawRoundedRectangle(0, 0, getWidth(), getHeight(), PluginNameGUI::corner_size, PluginNameGUI::line_thickness);
}

//==============================================================================
void PanelBase::mouseDown(const juce::MouseEvent& event)
{
    bool rightClick = juce::ModifierKeys::getCurrentModifiers().isPopupMenu();
    
    if (rightClick) {
        contextMenu->showMenu(getName());
    }
}
