/*
  ==============================================================================

    SidePanel.cpp
    Created: 25 Nov 2021 8:56:43am
    Author:  Nicholas Berriochoa

  ==============================================================================
*/

#include "SidePanel.h"

SidePanel::SidePanel(PluginNameAudioProcessor *inProcessor, ContextMenu *inContextMenu)
:   PanelBase(inProcessor, inContextMenu)
{
    setSize(SidePanelGUI::width, SidePanelGUI::height);
    setName("SidePanel");
    setComponentID("SidePanelID");
}

SidePanel::~SidePanel()
{
    
}

void SidePanel::resized()
{
    
}
