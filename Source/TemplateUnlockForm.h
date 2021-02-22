/*
  ==============================================================================

    TemplateUnlockForm.h
    Created: 22 Feb 2021 2:38:47pm
    Author:  Nicholas Berriochoa

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "TemplateMarketplaceStatus.h"

class TemplateUnlockForm
:   public juce::OnlineUnlockForm
{
public:
    TemplateUnlockForm(TemplateMarketplaceStatus& status);
    void dismiss() override;
    
private:
    
};
