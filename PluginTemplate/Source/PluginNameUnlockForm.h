/*
  ==============================================================================

    PluginNameUnlockForm.h
    Created: 12 Apr 2021 5:03:03pm
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
