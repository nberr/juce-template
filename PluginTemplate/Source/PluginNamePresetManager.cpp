/*
  ==============================================================================

    PluginNamePresetManager.cpp
    Created: 12 Apr 2021 5:00:55pm
    Author:  Nicholas Berriochoa

  ==============================================================================
*/

#include "PluginNamePresetManager.h"

#include "PluginNameParameters.h"
#include "PluginNameInternalParameters.h"

PluginNamePresetManager::PluginNamePresetManager(juce::AudioProcessor* inProcssor, juce::String inDirectory)
:   mCurrentPresetIsSaved(false),
    mCurrentPresetName("Untitled"),
    mProcessor(inProcssor)
{
    mPresetDirectory = inDirectory;
    
    if (!juce::File(mPresetDirectory).exists())
    {
        juce::File(mPresetDirectory).createDirectory();
    }
    
    storeLocalPreset();
}

PluginNamePresetManager::~PluginNamePresetManager()
{
    
}

void PluginNamePresetManager::getXmlForPreset(juce::XmlElement* inElement)
{
    auto& parameters = mProcessor->getParameters();
    
    for (int i = 0; i < parameters.size(); i++)
    {
        juce::AudioProcessorParameterWithID* parameter = (juce::AudioProcessorParameterWithID*)parameters.getUnchecked(i);
        
        inElement->setAttribute(parameter->paramID, parameter->getValue());
    }
}

void PluginNamePresetManager::loadPresetForXml(juce::XmlElement* inElement)
{
    mCurrentPresetXml = inElement;
    
    auto& parameters = mProcessor->getParameters();
    
    for (int i = 0; i < mCurrentPresetXml->getNumAttributes(); i++)
    {
        const juce::String paramID = mCurrentPresetXml->getAttributeName(i);
        const float value = mCurrentPresetXml->getDoubleAttribute(paramID);
        
        for (int j = 0; j < parameters.size(); j++) {
            juce::AudioProcessorParameterWithID* parameter = (juce::AudioProcessorParameterWithID*)parameters.getUnchecked(i);
            
            if (paramID == parameter->paramID)
            {
                parameter->setValueNotifyingHost(value);
            }
        }
    }
}

int PluginNamePresetManager::getNumberOfPresets()
{
    return mLocalPresets.size();
}

juce::String PluginNamePresetManager::getPresetName(int inPresetIndex)
{
    return mLocalPresets[inPresetIndex].getFileNameWithoutExtension();
}

void PluginNamePresetManager::createNewPreset()
{
    auto& parameters = mProcessor->getParameters();
    
    for (int i = 0; i < parameters.size(); i++)
    {
        juce::AudioProcessorParameterWithID* parameter = (juce::AudioProcessorParameterWithID*)parameters.getUnchecked(i);
        
        const float defaultValue = parameter->getDefaultValue();
        
        parameter->setValueNotifyingHost(defaultValue);
    }
    
    mCurrentPresetIsSaved = false;
    mCurrentPresetName = "Untitled";
}

void PluginNamePresetManager::savePreset()
{
    juce::MemoryBlock destinationData;
    mProcessor->getStateInformation(destinationData);
    
    mCurrentlyLoadedPreset.deleteFile();
    mCurrentlyLoadedPreset.appendData(destinationData.getData(),
                                      destinationData.getSize());
    
    mCurrentPresetIsSaved = true;
}

void PluginNamePresetManager::saveAsPreset(juce::String inPresetName)
{
    juce::File presetFile = juce::File(mPresetDirectory + DIR_SEP + inPresetName + PRESET_FILE_EXTENSION);
    
    if (!presetFile.exists())
    {
        presetFile.create();
    }
    else
    {
        presetFile.deleteFile();
    }
    
    juce::MemoryBlock destinationData;
    mProcessor->getStateInformation(destinationData);
    
    presetFile.appendData(destinationData.getData(),
                          destinationData.getSize());
    
    mCurrentPresetIsSaved = true;
    mCurrentPresetName = inPresetName;
    
    storeLocalPreset();
}

void PluginNamePresetManager::loadPreset(int inPresetIndex)
{
    mCurrentlyLoadedPreset = mLocalPresets[inPresetIndex];
    
    juce::MemoryBlock presetBinary;
    
    if (mCurrentlyLoadedPreset.loadFileAsData(presetBinary))
    {
        mCurrentPresetIsSaved = true;
        mCurrentPresetName = getPresetName(inPresetIndex);
        mProcessor->setStateInformation(presetBinary.getData(),
                                        (int)presetBinary.getSize());
    }
}

bool PluginNamePresetManager::getIsCurrentPresetSaved()
{
    return mCurrentPresetIsSaved;
}

juce::String PluginNamePresetManager::getCurrentPresetName()
{
    return mCurrentPresetName;
}

void PluginNamePresetManager::storeLocalPreset()
{
    mLocalPresets.clear();
        
    for (juce::DirectoryEntry entry: juce::RangedDirectoryIterator(juce::File(mPresetDirectory),
                                                                   false,
                                                                   "*" + (juce::String)PRESET_FILE_EXTENSION,
                                                                   juce::File::TypesOfFileToFind::findFiles))
    {
        juce::File preset = entry.getFile();
        mLocalPresets.add(preset);
    }
}
