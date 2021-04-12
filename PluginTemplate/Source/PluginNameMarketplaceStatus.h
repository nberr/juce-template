/*
  ==============================================================================

    PluginNameMarketplaceStatus.h
    Created: 12 Apr 2021 5:04:30pm
    Author:  Nicholas Berriochoa

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class PluginNameMarketplaceStatus
:   public juce::OnlineUnlockStatus
{
public:
    PluginNameMarketplaceStatus() = default;
    
    juce::String getProductID() override;
    bool doesProductIDMatch(const juce::String& returnedIDFromServer) override;
    juce::RSAKey getPublicKey() override;
    
    void saveState(const juce::String&) override;
    juce::String getState() override;
    
    juce::String getWebsiteName() override;
    juce::URL getServerAuthenticationURL() override;
    juce::String readReplyFromWebserver(const juce::String& email, const juce::String& password) override;
    
    void userCancelled() override;
    
private:
    juce::CriticalSection streamCreationLock;
    std::unique_ptr<juce::WebInputStream> stream;
};
