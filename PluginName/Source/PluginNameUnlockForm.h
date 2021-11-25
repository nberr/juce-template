/*
  ==============================================================================

    PluginNameUnlockForm.h
    Created: 25 Nov 2021 9:00:34am
    Author:  Nicholas Berriochoa

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#include "PluginNameMarketplaceStatus.h"

class PluginNameUnlockForm
:   public juce::OnlineUnlockForm
{
public:
    PluginNameUnlockForm(PluginNameMarketplaceStatus& status);
    void dismiss() override;
    
private:
    
};
