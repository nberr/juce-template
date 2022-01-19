/*
  ==============================================================================

    MainPanel.cpp
    Created: 25 Nov 2021 8:56:29am
    Author:  Nicholas Berriochoa

  ==============================================================================
*/

#include "MainPanel.h"

#include "PluginNameParameters.h"

//==============================================================================
MainPanel::MainPanel(PluginNameAudioProcessor* inProcessor, ContextMenu* inContextMenu)
:   PanelBase(inProcessor, inContextMenu),
    pChoice(inProcessor->parameters, "Choice"),
    pInt(inProcessor->parameters, "Int", "Parameter Int"),
    pFloat(inProcessor->parameters, "Float", "Parameter Float"),
    pBool(inProcessor->parameters, "Bool", "Parameter Bool")
{
    float scale = guiScale.getProperty(juce::Identifier("value"));
    setSize(MainPanelGUI::width * scale, MainPanelGUI::height * scale);
    setName("MainPanel");
    setComponentID("MainPanelID");
    
    pInt.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    pInt.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 0, 0);
    
    pFloat.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    pFloat.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 0, 0);
    
    int i = 1;
    for (juce::String choice : PluginNameParameters::Choices[3]) {
        pChoice.addItem(choice, i++);
    }
    
    pBool.setClickingTogglesState(true);
    
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
    float scale = guiScale.getProperty(juce::Identifier("value"));
    
    pInt.setBounds(0, 0, 50 * scale, 50 * scale);
    pFloat.setBounds(0, 50, 50, 50);
    pChoice.setBounds(100, 0, 100, 50);
    pBool.setBounds(100, 100, 100, 50);
}
