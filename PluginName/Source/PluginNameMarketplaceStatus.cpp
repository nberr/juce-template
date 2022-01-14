/*
  ==============================================================================

    PluginNameMarketplaceStatus.cpp
    Created: 25 Nov 2021 9:01:11am
    Author:  Nicholas Berriochoa

  ==============================================================================
*/

#include "PluginNameMarketplaceStatus.h"

//==============================================================================
juce::String PluginNameMarketplaceStatus::getProductID()
{
    return "PluginNameApp";
}

bool PluginNameMarketplaceStatus::doesProductIDMatch(const juce::String& returnedIDFromServer)
{
    return getProductID() == returnedIDFromServer;
}

juce::RSAKey PluginNameMarketplaceStatus::getPublicKey()
{
    return juce::RSAKey("PluginName_PUBLIC_KEY");
}

//==============================================================================
void PluginNameMarketplaceStatus::saveState(const juce::String&)
{
    
}

juce::String PluginNameMarketplaceStatus::getState()
{
    return {};
}

//==============================================================================
juce::String PluginNameMarketplaceStatus::getWebsiteName()
{
    return "nberr.io";
}

juce::URL PluginNameMarketplaceStatus::getServerAuthenticationURL()
{
    return juce::URL ("https://localhost:8443/auth.php");
}

juce::String PluginNameMarketplaceStatus::readReplyFromWebserver(const juce::String& email, const juce::String& password)
{
    juce::URL url (getServerAuthenticationURL()
                .withParameter ("product", getProductID())
                .withParameter ("email", email)
                .withParameter ("pw", password)
                .withParameter ("os", juce::SystemStats::getOperatingSystemName())
                .withParameter ("mach", getLocalMachineIDs()[0]));

    DBG ("Trying to unlock via URL: " << url.toString (true));

    {
        juce::ScopedLock lock (streamCreationLock);
        stream.reset (new juce::WebInputStream (url, true));
    }

    if (stream->connect (nullptr))
    {
        auto* thread = juce::Thread::getCurrentThread();

        if (thread->threadShouldExit() || stream->isError())
            return {};

        auto contentLength = stream->getTotalLength();
        auto downloaded    = 0;

        const size_t bufferSize = 0x8000;
        juce::HeapBlock<char> buffer (bufferSize);

        while (! (stream->isExhausted() || stream->isError() || thread->threadShouldExit()))
        {
            auto max = juce::jmin ((int) bufferSize, contentLength < 0 ? std::numeric_limits<int>::max()
                                                                 : static_cast<int> (contentLength - downloaded));

            auto actualBytesRead = stream->read (buffer.get() + downloaded, max - downloaded);

            if (actualBytesRead < 0 || thread->threadShouldExit() || stream->isError())
                break;

            downloaded += actualBytesRead;

            if (downloaded == contentLength)
                break;
        }

        if (thread->threadShouldExit() || stream->isError() || (contentLength > 0 && downloaded < contentLength))
            return {};

        return { juce::CharPointer_UTF8 (buffer.get()) };
    }

    return {};
}

//==============================================================================
void PluginNameMarketplaceStatus::userCancelled()
{
    juce::ScopedLock lock(streamCreationLock);
    
    if (stream != nullptr)
    {
        stream->cancel();
    }
}
