/*
  ==============================================================================

    MenuPanel.cpp
    Created: 25 Nov 2021 8:56:49am
    Author:  Nicholas Berriochoa

  ==============================================================================
*/

#include "MenuPanel.h"

#include "PluginNameParameters.h"

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
    mAdvButton.setBounds(getWidth()*0.1f, getHeight() * 0.50f, getWidth() * 0.8f, 40);
}

void MenuPanel::buttonClicked(juce::Button* b)
{
    if (b == &mAdvButton) {
        if (mAdvButton.getToggleState()) {
            PluginNameInternalParameters::showSidePanel = true;
        }
        else {
            PluginNameInternalParameters::showSidePanel = false;
        }
        getParentComponent()->resized();
    }
}
