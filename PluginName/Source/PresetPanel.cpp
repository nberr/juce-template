/*
  ==============================================================================

    PresetPanel.cpp
    Created: 25 Nov 2021 8:56:36am
    Author:  Nicholas Berriochoa

  ==============================================================================
*/

#include "PresetPanel.h"

#include "PresetOverlay.h"

PresetPanel::PresetPanel(PluginNameAudioProcessor* inProcessor, ContextMenu* inContextMenu)
:   PanelBase(inProcessor, inContextMenu)
{
    float scale = PluginNameInternalParameters::GUIScale;
    setSize(PresetPanelGUI::width * scale, PresetPanelGUI::height * scale);
    setName("PresetPanel");
    setComponentID("PresetPanelID");
    
    for (juce::TextButton* button : buttons) {
        button->setTriggeredOnMouseDown(true);
        button->addListener(this);
        addAndMakeVisible(button);
    }
    
    // TODO: set the text to the current preset
    // TODO: set arrow based on if A or B is selected
}

PresetPanel::~PresetPanel()
{
    // TODO: why do we do this?
    buttons.clear();
    buttons.shrink_to_fit();
}

void PresetPanel::resized()
{
    float scale = PluginNameInternalParameters::GUIScale;
    
    // undo, redo
    undo.setBounds(0, 0,
                   PresetPanelGUI::undo_redo_width * scale,
                   PresetPanelGUI::undo_redo_height * scale);
    redo.setBounds(undo.getRight() + 5, 0,
                   PresetPanelGUI::undo_redo_width * scale,
                   PresetPanelGUI::undo_redo_height * scale);
    
    // prev, menu, next
    prevPreset.setBounds(redo.getRight() + 40, 0,
                         PresetPanelGUI::change_preset_width * scale,
                         PresetPanelGUI::change_preset_height * scale);
    presetMenu.setBounds(prevPreset.getRight() + 5, 0,
                         PresetPanelGUI::preset_display_width * scale,
                         PresetPanelGUI::preset_display_height * scale);
    nextPreset.setBounds(presetMenu.getRight() + 5, 0,
                         PresetPanelGUI::change_preset_width * scale,
                         PresetPanelGUI::change_preset_height * scale);
    
    // A, copy, B
    presetA.setBounds(nextPreset.getRight() + 40, 0,
                      PresetPanelGUI::A_B_Copy_width * scale,
                      PresetPanelGUI::A_B_Copy_height * scale);
    presetCopy.setBounds(presetA.getRight() + 5, 0,
                         PresetPanelGUI::A_B_Copy_width * scale,
                         PresetPanelGUI::A_B_Copy_height * scale);
    presetB.setBounds(presetCopy.getRight() + 5, 0,
                      PresetPanelGUI::A_B_Copy_width * scale,
                      PresetPanelGUI::A_B_Copy_height * scale);
}

void PresetPanel::buttonClicked(juce::Button* b)
{
    bool rightClick = juce::ModifierKeys::getCurrentModifiers().isPopupMenu();
    
    if (rightClick) {
        mContextMenu->showMenu(b->getName());
        auto editor = findParentComponentOfClass<juce::AudioProcessorEditor>();
        editor->resized();
        resized();
    }
    else {
        if (b == &prevPreset)
        {
            
        }
        else if (b == &nextPreset)
        {
            
        }
        else if (b == &presetMenu)
        {
            // toggle overlay
            juce::Component* overlay = getParentComponent()->findChildWithID("PresetOverlayID");
            if (overlay != nullptr) {
                overlay->setVisible(!overlay->isVisible());
            }
        }
    }
}
