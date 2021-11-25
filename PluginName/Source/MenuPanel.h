/*
  ==============================================================================

    MenuPanel.h
    Created: 25 Nov 2021 8:56:49am
    Author:  Nicholas Berriochoa

  ==============================================================================
*/

#pragma once

#include "PanelBase.h"

class MenuPanel
:   public PanelBase,
    public juce::Button::Listener
{
public:
    MenuPanel(PluginNameAudioProcessor *inProcessor, ContextMenu *inContextMenu);
    ~MenuPanel();
    
    void resized() override;
    void buttonClicked(juce::Button* b) override;
    
private:
    juce::TextButton mAdvButton{"ADV"};
};
