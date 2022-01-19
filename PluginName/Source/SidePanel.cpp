/*
  ==============================================================================

    SidePanel.cpp
    Created: 25 Nov 2021 8:56:43am
    Author:  Nicholas Berriochoa

  ==============================================================================
*/

#include "SidePanel.h"

//==============================================================================
SidePanel::SidePanel(PluginNameAudioProcessor *inProcessor, ContextMenu *inContextMenu)
:   PanelBase(inProcessor, inContextMenu)
{
    setName("SidePanel");
    setComponentID("SidePanelID");
}

SidePanel::~SidePanel()
{
    
}

//==============================================================================
void SidePanel::resized()
{
    //float scale = guiScale.getProperty(juce::Identifier("value"));

}
