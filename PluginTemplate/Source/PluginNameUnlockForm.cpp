/*
  ==============================================================================

    PluginNameUnlockForm.cpp
    Created: 12 Apr 2021 5:03:03pm
    Author:  Nicholas Berriochoa

  ==============================================================================
*/

#include "PluginNameUnlockForm.h"

PluginNameUnlockForm::PluginNameUnlockForm(PluginNameMarketplaceStatus& status)
:   juce::OnlineUnlockForm(status, "Please provide your email and password.")
{
    
}

void PluginNameUnlockForm::dismiss()
{
    setVisible(false);
}
