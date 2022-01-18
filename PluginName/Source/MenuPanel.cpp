/*
  ==============================================================================

    MenuPanel.cpp
    Created: 25 Nov 2021 8:56:49am
    Author:  Nicholas Berriochoa

  ==============================================================================
*/

#include "MenuPanel.h"

#include "PluginNameParameters.h"
#include "PluginEditor.h"

//==============================================================================
MenuPanel::MenuPanel(PluginNameAudioProcessor *inProcessor, ContextMenu *inContextMenu)
:   PanelBase(inProcessor, inContextMenu)
{
    setName("MenuPanel");
    
    // initialize each button and add them to the scene
    for (juce::TextButton* button : buttons) {
        button->setTriggeredOnMouseDown(true);
        button->addListener(this);
        addAndMakeVisible(button);
    }
    
    // master and advanced need to be toggleable 
    masterButton.setClickingTogglesState(true);
    advancedButton.setClickingTogglesState(true);
}

MenuPanel::~MenuPanel()
{
    
}

//==============================================================================
void MenuPanel::resized()
{
    masterButton.setBounds(getWidth()*0.1f, getHeight() * 0.50f, getWidth() * 0.8f, 40);
    advancedButton.setBounds(getWidth()*0.1f, masterButton.getBottom() + 10, getWidth() * 0.8f, 40);
    accountButton.setBounds(getWidth()*0.1f, advancedButton.getBottom() + 10, getWidth() * 0.8f, 40);
}

//==============================================================================
void MenuPanel::buttonClicked(juce::Button* b)
{
    bool rightClick = juce::ModifierKeys::getCurrentModifiers().isPopupMenu();
    
    if (rightClick) {
        mContextMenu->showMenu(b->getName());
        auto editor = findParentComponentOfClass<juce::AudioProcessorEditor>();
        editor->resized();
        resized();
    }
    else {
        if (b == &masterButton) {
            PluginNameInternalParameters::masterOnOff = !PluginNameInternalParameters::masterOnOff;
        }
        else if (b == &advancedButton) {
            if (advancedButton.getToggleState()) {
                PluginNameInternalParameters::showSidePanel = true;
            }
            else {
                PluginNameInternalParameters::showSidePanel = false;
            }
            getParentComponent()->resized();
        }
        else if (b == &accountButton) {
            auto editor = (PluginNameAudioProcessorEditor *)getParentComponent();
            editor->showForm();
        }
    }
}
