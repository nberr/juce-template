/*
  ==============================================================================

    PluginNameUnlockForm.cpp
    Created: 25 Nov 2021 9:00:34am
    Author:  Nicholas Berriochoa

  ==============================================================================
*/

#include "PluginNameUnlockForm.h"

//==============================================================================
PluginNameUnlockForm::PluginNameUnlockForm(PluginNameMarketplaceStatus& status)
:   juce::OnlineUnlockForm(status, "Please provide your email and password.")
{
    
}

void PluginNameUnlockForm::dismiss()
{
    setVisible(false);
}
