/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

#include "PluginNameGUI.h"

//==============================================================================
PluginNameAudioProcessorEditor::PluginNameAudioProcessorEditor (PluginNameAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p),
    contextMenu(&audioProcessor),
    menuPanel(&audioProcessor, &contextMenu),
    presetPanel(&audioProcessor, &contextMenu),
    mainPanel(&audioProcessor, &contextMenu),
    sidePanel(&audioProcessor, &contextMenu),
    displayPresetOverlay(&audioProcessor, &contextMenu),
    savePresetOverlay(&audioProcessor, &contextMenu),
    deletePresetOverlay(&audioProcessor, &contextMenu),
    updatePresetOverlay(&audioProcessor, &contextMenu),
    unlockForm(marketplaceStatus)
{
    // JUCE UI implementation
    
    // initialize the main window
    setName("PluginEditor");
    setComponentID("PluginEditorID");
    setSize(PluginNameGUI::width, PluginNameGUI::height);
    setResizable(false, false);
    
    // add each panel to the scene
    for (PanelBase* panel : panels) {
        addAndMakeVisible(panel);
    }
    
    // add overlays to the scene but don't make them visible
    for (PanelBase* overlay : overlays) {
        
        overlay->setAlwaysOnTop(true);
        addChildComponent(overlay);
    }
        
    juce::ValueTree ssp = audioProcessor.settings.getChild(PluginNameSettings::PNS_showSidePanel);
    PluginNameSettings::showSidePanel = ssp.getProperty(juce::Identifier("value"));
    
    // initialize the unlock form
    // add to scene but don't make visible
    unlockForm.setAlwaysOnTop(true);
    addChildComponent(unlockForm);
    
    unlockButton.setSize(100, 100);
    unlockButton.setTopLeftPosition(50, 50);
    unlockButton.onClick = [this] {
        unlockForm.setVisible(true);
    };
    //addAndMakeVisible (unlockButton);

    secretButton.setEnabled (false);
    secretButton.onClick = [this] { checkFeature(); };
    //addAndMakeVisible (secretButton);

    startTimer(100);
}

PluginNameAudioProcessorEditor::~PluginNameAudioProcessorEditor()
{
}

//==============================================================================
void PluginNameAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
}

void PluginNameAudioProcessorEditor::resized()
{
    // JUCE UI implementation
    juce::ValueTree guiScale = audioProcessor.settings.getChild(PluginNameSettings::PNS_GUIScale);
    float scale = guiScale.getProperty(juce::Identifier("value"));
    
    int width = PluginNameGUI::width;
    if (PluginNameSettings::showSidePanel) {
        width += SidePanelGUI::width;
    }
        
    setSize(width * scale, PluginNameGUI::height * scale);
        
    menuPanel.setBounds(0, 0,
                         MenuPanelGUI::width * scale,
                         MenuPanelGUI::height * scale);
    presetPanel.setBounds(menuPanel.getRight(), 0,
                           PresetPanelGUI::width * scale,
                           PresetPanelGUI::height * scale);
    mainPanel.setBounds(menuPanel.getRight(), presetPanel.getBottom(),
                         MainPanelGUI::width * scale,
                         MainPanelGUI::height * scale);
    sidePanel.setBounds(mainPanel.getRight(), 0,
                         SidePanelGUI::width * scale,
                         SidePanelGUI::height * scale);
    
    // overlays
    displayPresetOverlay.setBounds(menuPanel.getRight(), presetPanel.getBottom(),
                             MainPanelGUI::width * scale,
                             MainPanelGUI::height * scale);
    
    savePresetOverlay.setBounds(0, 0, getWidth(), getHeight());
    
    unlockForm.setBounds(0, 0, getWidth(), getHeight());

    // React UI implementation
    //appRoot.setBounds(getLocalBounds());
}

//==============================================================================
void PluginNameAudioProcessorEditor::timerCallback()
{
    // need this to resize the plugin form the context menu
    resized();
    
    // check if the plugin is unlocked
    if (! isUnlocked && marketplaceStatus.isUnlocked())
    {
        isUnlocked = true;
        unlockApp();
    }
}

void PluginNameAudioProcessorEditor::unlockApp()
{
    unlockForm.setVisible(false);
    
    secretButton.setEnabled(true);
    unlockButton.setEnabled(false);
}

void PluginNameAudioProcessorEditor::checkFeature()
{
    if (marketplaceStatus.isUnlocked())
        DBG ("App unlocked!");
    else
        DBG ("Beware of hackers!");
}
