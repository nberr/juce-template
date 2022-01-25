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
    setName("MainPanel");
    setComponentID("MainPanelID");
    
    pInt.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    pInt.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 0, 0);
    pInt.addListener(this);
    
    pFloat.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    pFloat.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 0, 0);
    pFloat.addListener(this);
    
    int i = 1;
    for (juce::String choice : PluginNameParameters::Choices[3]) {
        pChoice.addItem(choice, i++);
    }
    pChoice.addListener(this);
    
    pBool.addListener(this);
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

//==============================================================================
void MainPanel::buttonClicked(juce::Button* b)
{
    if (b == &pBool) {
        mProcessor->getPresetManager()->updateQuickPreset();
    }
}

void MainPanel::sliderValueChanged(juce::Slider* s)
{
    if (s == &pInt) {
        mProcessor->getPresetManager()->updateQuickPreset();
    }
    else if (s == &pFloat) {
        mProcessor->getPresetManager()->updateQuickPreset();
    }
}

void MainPanel::comboBoxChanged(juce::ComboBox* cb)
{
    if (cb == &pChoice) {
        mProcessor->getPresetManager()->updateQuickPreset();
    }
}
