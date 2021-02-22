/*
  ==============================================================================

    TemplateUnlockForm.cpp
    Created: 22 Feb 2021 2:38:47pm
    Author:  Nicholas Berriochoa

  ==============================================================================
*/

#include "TemplateUnlockForm.h"

TemplateUnlockForm::TemplateUnlockForm(TemplateMarketplaceStatus& status)
:   juce::OnlineUnlockForm(status, "Please provide your email and password.")
{
    
}

void TemplateUnlockForm::dismiss()
{
    setVisible(false);
}
