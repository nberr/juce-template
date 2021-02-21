/*
  ==============================================================================

    MainPanel.cpp
    Created: 21 Feb 2021 6:51:19pm
    Author:  Nicholas Berriochoa

  ==============================================================================
*/

#include "MainPanel.h"

MainPanel::MainPanel(Template_AudioProcessor *inProcessor)
:   PanelBase(inProcessor)
{
    setSize(MAIN_PANEL_WIDTH, MAIN_PANEL_HEIGHT);
}

MainPanel::~MainPanel()
{
    
}
