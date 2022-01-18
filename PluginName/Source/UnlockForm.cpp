/*
  ==============================================================================

    UnlockForm.cpp
    Created: 25 Nov 2021 9:00:34am
    Author:  Nicholas Berriochoa

  ==============================================================================
*/

#include "UnlockForm.h"

//==============================================================================
UnlockForm::UnlockForm(MarketplaceStatus& status)
:   juce::OnlineUnlockForm(status, "Please provide your email and password.")
{
    
}

void UnlockForm::dismiss()
{
    setVisible(false);
}
