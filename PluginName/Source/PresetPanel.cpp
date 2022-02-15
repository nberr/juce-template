/*
  ==============================================================================

    PresetPanel.cpp
    Created: 25 Nov 2021 8:56:36am
    Author:  Nicholas Berriochoa

  ==============================================================================
*/

#include "PresetPanel.h"

#include "PresetManager.h"

//==============================================================================
PresetPanel::PresetPanel(PluginNameAudioProcessor *processor, ContextMenu *contextMenu)
:   PanelBase(processor, contextMenu)
{
    setName("PresetPanel");
    setComponentID("PresetPanelID");
    
    undoManager = processor->getUndoManager();
    
    // initialize each button and add them to the scene
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

//==============================================================================
void PresetPanel::resized()
{
    float scale = guiScale.getProperty(juce::Identifier("value"));;
    float centered_height = (PresetPanelGUI::height - PresetPanelGUI::undo_redo_height) * 0.5f * scale;
    int buffer = 5 * scale;
    
    setSize(PresetPanelGUI::width * scale, PresetPanelGUI::height * scale);
    
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

//==============================================================================
void PresetPanel::buttonClicked(juce::Button* b)
{
    bool rightClick = juce::ModifierKeys::getCurrentModifiers().isPopupMenu();
    
    if (rightClick) {
        contextMenu->showMenu(b->getName());
        auto editor = findParentComponentOfClass<juce::AudioProcessorEditor>();
        editor->resized();
        resized();
    }
    else {
        if (b == &undo) {
            undoManager->undo();
        }
        else if (b == &redo) {
            undoManager->redo();
        }
        else if (b == &prevPreset) {
            auto pm = processor->getPresetManager();
            pm->loadPreviousPreset();
            presetMenu.setButtonText(pm->getCurrentPresetName());
        }
        else if (b == &presetMenu) {
            // toggle overlay
            juce::Component* overlay = getParentComponent()->findChildWithID("PresetDisplayOverlayID");
            if (overlay != nullptr) {
                overlay->setVisible(!overlay->isVisible());
            }
        }
        else if (b == &nextPreset) {
            auto pm = processor->getPresetManager();
            pm->loadNextPreset();
            presetMenu.setButtonText(pm->getCurrentPresetName());
        }
        else if (b == &presetA || b == &presetB) {
            
            switch(processor->getPresetManager()->quickPresetInUse) {
                case PresetManager::QuickPreset::Preset_A:
                    
                    presetCopy.setButtonText("<-");
                    
                    break;
                case PresetManager::QuickPreset::Preset_B:
                    
                    presetCopy.setButtonText("->");
                    
                    break;
                default:
                    jassertfalse;
            }
            
            processor->getPresetManager()->toggleQuickPreset();
        }
        else if (b == &presetCopy) {
            processor->getPresetManager()->copyQuickPreset();
        }
    }
}

//==============================================================================
void PresetPanel::setPresetMenu(juce::String presetName)
{
    presetMenu.setButtonText(presetName);
}
