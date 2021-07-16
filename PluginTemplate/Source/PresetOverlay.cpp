/*
  ==============================================================================

    PresetOverlay.cpp
    Created: 9 Jun 2021 5:47:45pm
    Author:  Nicholas Berriochoa

  ==============================================================================
*/

#include "PresetOverlay.h"

#include "PresetButtonPropertyComponent.h"

PresetOverlay::PresetOverlay(PluginNameAudioProcessor* inProcessor, ContextMenu* inContextMenu)
:   PanelBase(inProcessor, inContextMenu)
{
    setName("PresetOverlay");
    setComponentID("PresetOverlayID");
    setOpaque(true);
    
    mAddNewPreset.setButtonText("+");
    mAddNewPreset.setTriggeredOnMouseDown(true);
    mAddNewPreset.addListener(this);
    addAndMakeVisible(&mAddNewPreset);
    
    mSetDefault.setButtonText("default");
    mSetDefault.setTriggeredOnMouseDown(true);
    mSetDefault.addListener(this);
    addAndMakeVisible(&mSetDefault);
    
    mDismissOverlay.setButtonText("x");
    mDismissOverlay.setTriggeredOnMouseDown(true);
    mDismissOverlay.addListener(this);
    addAndMakeVisible(&mDismissOverlay);
    
    
    auto* panel = new juce::PropertyPanel ("Presets");
    panel->addSection("User Presets", getUserPresets(), true);
    panel->addSection("Presets", getUserPresets(), true);
    mPresetDisplay.addPanel(-1, panel, true);
    addAndMakeVisible(&mPresetDisplay);
}

PresetOverlay::~PresetOverlay()
{
    
}

void PresetOverlay::resized()
{
    float scale = *mContextMenu->mGUIScale;
    
    mAddNewPreset.setBounds(0, 0, PresetOverlayGUI::button_width * scale, PresetOverlayGUI::button_height * scale);
    mSetDefault.setBounds(PresetOverlayGUI::button_width * scale, 0, PresetOverlayGUI::button_width * scale, PresetOverlayGUI::button_height * scale);
    mDismissOverlay.setBounds(getWidth() - (PresetOverlayGUI::button_width * scale), 0, PresetOverlayGUI::button_width * scale, PresetOverlayGUI::button_height * scale);
    
    mPresetDisplay.setBounds(0, PresetOverlayGUI::button_height * scale, getWidth(), getHeight() - (PresetOverlayGUI::button_height * scale));
}

void PresetOverlay::buttonClicked(juce::Button* b)
{
    bool rightClick = juce::ModifierKeys::getCurrentModifiers().isPopupMenu();
    
    if (rightClick) {
        
    }
    else {
        if (b == &mAddNewPreset) {
            // display save preset overlay
            getParentComponent()->findChildWithID("SavePresetOverlayID")->setVisible(true);
            
        }
        else if (b == &mSetDefault) {
            // set default
        }
        else if (b == &mDismissOverlay) {
            setVisible(false);
        }
    }
}

juce::Array<juce::PropertyComponent*> PresetOverlay::getPresets()
{
    juce::Array<juce::PropertyComponent*> comps;
    
    
    
    return comps;
}

juce::Array<juce::PropertyComponent*> PresetOverlay::getUserPresets()
{
    juce::Array<juce::PropertyComponent*> comps;
    for (int i = 0; i < 5; ++i)
            comps.add (new PresetButtonPropertyComponent ("Button"));
    
    return comps;
}
