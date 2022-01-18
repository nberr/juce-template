/*
  ==============================================================================

    SettingsManager.cpp
    Created: 17 Jan 2022 6:52:58pm
    Author:  Nicholas Berriochoa

  ==============================================================================
*/

#include "SettingsManager.h"

SettingsManager::SettingsManager(juce::AudioProcessor* inProcssor)
{
    mProcessor = inProcssor;
    
    // create the settings folder if it doesn't exist
    juce::String dir_sep = juce::File::getSeparatorString();
    settingsDirectory = juce::File::getSpecialLocation(juce::File::userMusicDirectory).getFullPathName()
                        + dir_sep + JucePlugin_Manufacturer
                        + dir_sep + JucePlugin_Name;
    
    if (!juce::File(settingsDirectory).exists())
    {
        juce::File(settingsDirectory).createDirectory();
        
        // create the settings file
        std::unique_ptr<juce::XmlElement> xml = settings.createXml();
        xml->writeTo(settingsDirectory + dir_sep + "settings.xml");
    }
}

SettingsManager::~SettingsManager()
{
    
}

//==============================================================================
void SettingsManager::saveSettings()
{
    DBG("settings saved");
}
