/*
  ==============================================================================

    MainPanel.h
    Created: 21 Feb 2021 6:51:19pm
    Author:  Nicholas Berriochoa

  ==============================================================================
*/

#pragma once

#include "PanelBase.h"

#include "TemplateMarketplaceStatus.h"
#include "TemplateUnlockForm.h"

class MainPanel
:   public PanelBase,
    private juce::Timer
{
public:
    MainPanel(Template_AudioProcessor* inProcessor);
    ~MainPanel();
private:
    void timerCallback() override;
    void showForm();
    void unlockApp();
    void checkFeature();
    
    juce::Label      unlockLabel  { {}, "Status: Locked" };
    juce::TextButton unlockButton { "Unlock" },
                     secretButton { "Super Secret Feature" };

    TemplateMarketplaceStatus marketplaceStatus;
    TemplateUnlockForm unlockForm;

    bool isUnlocked = false;
};
