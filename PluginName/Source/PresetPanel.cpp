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
    // shrink_to_fit is required because gcc and clang does not actually free
    // any memory with clear
    buttons.clear();
    buttons.shrink_to_fit();
}

void PresetPanel::resized()
{
    float scale = PluginNameInternalParameters::GUIScale;
    float centered_height = (PresetPanelGUI::height - PresetPanelGUI::undo_redo_height) * 0.5f * scale;
    int buffer = 5 * scale;
    
    // undo, redo
    undo.setBounds(buffer, centered_height,
                   PresetPanelGUI::undo_redo_width * scale,
                   PresetPanelGUI::undo_redo_height * scale);
    redo.setBounds(undo.getRight() + buffer, centered_height,
                   PresetPanelGUI::undo_redo_width * scale,
                   PresetPanelGUI::undo_redo_height * scale);
    
    // prev, menu, next
    presetMenu.setBounds((PresetPanelGUI::width - PresetPanelGUI::preset_display_width) * 0.5f * scale,
                         centered_height,
                         PresetPanelGUI::preset_display_width * scale,
                         PresetPanelGUI::preset_display_height * scale);
    
    prevPreset.setBounds((presetMenu.getX() - buffer - (PresetPanelGUI::change_preset_width * scale)),
                         centered_height,
                         PresetPanelGUI::change_preset_width * scale,
                         PresetPanelGUI::change_preset_height * scale);
    
    nextPreset.setBounds((presetMenu.getRight() + buffer),
                         centered_height,
                         PresetPanelGUI::change_preset_width * scale,
                         PresetPanelGUI::change_preset_height * scale);
    
    // A, copy, B
    presetB.setBounds((PresetPanelGUI::width * scale) - (PresetPanelGUI::A_B_Copy_width * scale) - buffer,
                      centered_height,
                      PresetPanelGUI::A_B_Copy_width * scale,
                      PresetPanelGUI::A_B_Copy_height * scale);
    
    presetCopy.setBounds(presetB.getX() - buffer - (PresetPanelGUI::A_B_Copy_width * scale),
                         centered_height,
                         PresetPanelGUI::A_B_Copy_width * scale,
                         PresetPanelGUI::A_B_Copy_height * scale);
    presetA.setBounds(presetCopy.getX() - buffer - (PresetPanelGUI::A_B_Copy_width * scale),
                      centered_height,
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
