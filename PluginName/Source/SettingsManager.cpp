/*
  ==============================================================================

    SettingsManager.cpp
    Created: 17 Jan 2022 6:52:58pm
    Author:  Nicholas Berriochoa

  ==============================================================================
*/

#include "SettingsManager.h"

#include "PluginNameSettings.h"

SettingsManager::SettingsManager(juce::AudioProcessor* inProcssor, juce::ValueTree* inSettings)
{
    mProcessor = inProcssor;
    settings = inSettings;
    
    juce::String dir_sep = juce::File::getSeparatorString();
    settingsDirectory = juce::File::getSpecialLocation(juce::File::userMusicDirectory).getFullPathName()
                        + dir_sep + JucePlugin_Manufacturer
                        + dir_sep + JucePlugin_Name;
    settingsXML = settingsDirectory + dir_sep + "settings.xml";
    
    // create the directory heirarchy if it doesn't exist
    if (!juce::File(settingsDirectory).exists())
    {
        juce::File(settingsDirectory).createDirectory();
        
        // if creating the hierarchy failed, exit
        if (!juce::File(settingsDirectory).exists()) {
            jassertfalse;
        }
    }
    
    // load the settings file or create one if it doesn't exist
    if (juce::File(settingsXML).exists()) {
        // TODO: file already exists. load the file into the ValueTree
        loadSettings();
        
        // file loaded is invalid
        if (!settings->isValid()) {
            jassertfalse;
        }
    }
    else {
        createSettingsLayout();
        
        if (!settings->isValid()) {
            jassertfalse;
        }

        std::unique_ptr<juce::XmlElement> xml = settings->createXml();
        xml->writeTo(settingsXML);
        
        // double check that the file was actually created
        if (!juce::File(settingsXML).exists()) {
            jassertfalse;
        }
    }
}

SettingsManager::~SettingsManager()
{
    
}

//==============================================================================
void SettingsManager::saveSettings()
{
    if (!settings->isValid()) {
        jassertfalse;
    }

    std::unique_ptr<juce::XmlElement> xml = settings->createXml();
    xml->writeTo(settingsXML);
    
    // double check that the file was actually created
    if (!juce::File(settingsXML).exists()) {
        jassertfalse;
    }
}

void SettingsManager::loadSettings()
{
    juce::XmlDocument xmlDoc {juce::File(settingsXML)};
    juce::XmlElement element = *xmlDoc.getDocumentElement();
    
    *settings = juce::ValueTree::fromXml(element);
}

//==============================================================================
void SettingsManager::createSettingsLayout()
{
    juce::ValueTree *layout = settings;
    *layout = juce::ValueTree(juce::Identifier("Settings"));
    juce::Identifier settingNode ("Setting");
    
    juce::Identifier id ("id");
    juce::Identifier value ("value");
    
    for (int index = 0; index < PluginNameSettings::PNS_TotalNumSettings; index++) {
        layout->addChild(juce::ValueTree(settingNode), index, nullptr);
        auto child = layout->getChild(index);
        child.setProperty(id, PluginNameSettings::IDs[index], nullptr);
        child.setProperty(value, PluginNameSettings::Values[index], nullptr);
    }
}
