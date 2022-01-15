/*
  ==============================================================================

    MenuPanel.h
    Created: 25 Nov 2021 8:56:49am
    Author:  Nicholas Berriochoa

  ==============================================================================
*/

#pragma once

#include "PanelBase.h"

//==============================================================================
class MenuPanel
:   public PanelBase,
    public juce::Button::Listener
{
public:
    //==============================================================================
    MenuPanel(PluginNameAudioProcessor *inProcessor, ContextMenu *inContextMenu);
    ~MenuPanel();
    
    //==============================================================================
    void resized() override;
    
    //==============================================================================
    void buttonClicked(juce::Button* b) override;
    
private:
    //==============================================================================
    // plugin logo
    
    // display info
    // extra buttons

    juce::TextButton masterButton{"master"};
    juce::TextButton advancedButton{"advanced"};
    juce::TextButton accountButton{"account"};
    
    // company logo
    
    //==============================================================================
    std::vector<juce::TextButton*> buttons = {
        &masterButton, &advancedButton, &accountButton
    };
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MenuPanel)
};
