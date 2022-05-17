/*
  ==============================================================================

    SidePanel.cpp
    Created: 25 Nov 2021 8:56:43am
    Author:  Nicholas Berriochoa

  ==============================================================================
*/

#include "SidePanel.h"

//==============================================================================
SidePanel::SidePanel(PluginNameAudioProcessor *processor, ContextMenu *contextMenu)
:   PanelBase(processor, contextMenu)
{
    setName("SidePanel");
    setComponentID("SidePanelID");
    
    // addAndMakeVisible(b);
}

SidePanel::~SidePanel()
{
    
}

//==============================================================================
void SidePanel::resized()
{
    float scale = guiScale.getProperty(juce::Identifier("value"));
    b.setBounds(0, 0, 20 * scale, 20 * scale);
}
