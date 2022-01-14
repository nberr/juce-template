/*
  ==============================================================================

    MainPanel.cpp
    Created: 25 Nov 2021 8:56:29am
    Author:  Nicholas Berriochoa

  ==============================================================================
*/

#include "MainPanel.h"

//==============================================================================
MainPanel::MainPanel(PluginNameAudioProcessor* inProcessor, ContextMenu* inContextMenu)
:   PanelBase(inProcessor, inContextMenu),
    pChoice(inProcessor->parameters, "Choice"),
    pInt(inProcessor->parameters, "Int", "Parameter Int"),
    pFloat(inProcessor->parameters, "Float", "Parameter Float"),
    pBool(inProcessor->parameters, "Bool", "Parameter Bool")
{
    float scale = PluginNameInternalParameters::GUIScale;
    setSize(MainPanelGUI::width * scale, MainPanelGUI::height * scale);
    setName("MainPanel");
    setComponentID("MainPanelID");
    
    addAndMakeVisible(pInt);
    addAndMakeVisible(pFloat);
    addAndMakeVisible(pChoice);
    addAndMakeVisible(pBool);
    
}

MainPanel::~MainPanel()
{
    
}

//==============================================================================
void MainPanel::resized()
{
    // float scale = PluginNameInternalParameters::GUIScale;
    
    //pInt.setBounds(0, 0, 50, 50);
    //pFloat.setBounds(0, 50, 50, 50);
    //pChoice.setBounds(100, 0, 100, 50);
    //pBool.setBounds(100, 100, 50, 50);
}
