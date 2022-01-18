/*
  ==============================================================================

    UnlockForm.h
    Created: 25 Nov 2021 9:00:34am
    Author:  Nicholas Berriochoa

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#include "MarketplaceStatus.h"

//==============================================================================
class UnlockForm
:   public juce::OnlineUnlockForm
{
public:
    //==============================================================================
    UnlockForm(MarketplaceStatus& status);
    void dismiss() override;
    
private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (UnlockForm)
};
