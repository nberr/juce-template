/*
  ==============================================================================

    MenuPanel.cpp
    Created: 25 Nov 2021 8:56:49am
    Author:  Nicholas Berriochoa

  ==============================================================================
*/

#include "MenuPanel.h"

MenuPanel::MenuPanel(PluginNameAudioProcessor *inProcessor, ContextMenu *inContextMenu)
:   PanelBase(inProcessor, inContextMenu)
{
    setName("MenuPanel");
    
    mAdvButton.setClickingTogglesState(true);
    mAdvButton.addListener(this);
    addAndMakeVisible(mAdvButton);
}

MenuPanel::~MenuPanel()
{
    
}

void MenuPanel::resized()
{
    mAdvButton.setBounds(0, getHeight() * 0.50f, getWidth(), 40);
}

void MenuPanel::buttonClicked(juce::Button* b)
{
    if (b == &mAdvButton) {
        if (mAdvButton.getToggleState()) {
            //mProcessor->internalParameters.mShowSidePanel = true;
        }
        else {
            //mProcessor->internalParameters.mShowSidePanel = false;
        }
        getParentComponent()->resized();
    }
}
