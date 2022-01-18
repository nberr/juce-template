/*
  ==============================================================================

    PresetManager.cpp
    Created: 25 Nov 2021 9:02:19am
    Author:  Nicholas Berriochoa

  ==============================================================================
*/

#include "PresetManager.h"

//==============================================================================
PresetManager::PresetManager(juce::AudioProcessor* inProcssor)
:   mCurrentPresetIsSaved(false),
    mCurrentPresetName("Untitled"),
    mProcessor(inProcssor)
{
    juce::String dir_sep = juce::File::getSeparatorString();
    mPresetDirectory = juce::File::getSpecialLocation(juce::File::userMusicDirectory).getFullPathName()
                       + dir_sep + JucePlugin_Manufacturer
                       + dir_sep + JucePlugin_Name
                       + dir_sep + "Presets";
    
    if (!juce::File(mPresetDirectory).exists())
    {
        juce::File(mPresetDirectory).createDirectory();
    }
    
    storeLocalPreset();
}

PresetManager::~PresetManager()
{
    
}

//==============================================================================
void PresetManager::getXmlForPreset(juce::XmlElement* inElement)
{
    auto& parameters = mProcessor->getParameters();
    
    for (int i = 0; i < parameters.size(); i++)
    {
        juce::AudioProcessorParameterWithID* parameter = (juce::AudioProcessorParameterWithID*)parameters.getUnchecked(i);
        
        inElement->setAttribute(parameter->paramID, parameter->getValue());
    }
}

void PresetManager::loadPresetForXml(juce::XmlElement* inElement)
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

//==============================================================================
int PresetManager::getNumberOfPresets()
{
    return mLocalPresets.size();
}

juce::String PresetManager::getPresetName(int inPresetIndex)
{
    return mLocalPresets[inPresetIndex].getFileNameWithoutExtension();
}

//==============================================================================
void PresetManager::createNewPreset()
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

void PresetManager::savePreset()
{
    juce::MemoryBlock destinationData;
    mProcessor->getStateInformation(destinationData);
    
    mCurrentlyLoadedPreset.deleteFile();
    mCurrentlyLoadedPreset.appendData(destinationData.getData(),
                                      destinationData.getSize());
    
    mCurrentPresetIsSaved = true;
}

void PresetManager::saveAsPreset(juce::String inPresetName)
{
    juce::String dir_sep = juce::File::getSeparatorString();
    juce::File presetFile = juce::File(mPresetDirectory + dir_sep + inPresetName + PRESET_FILE_EXTENSION);
    
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

void PresetManager::loadPreset(int inPresetIndex)
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

//==============================================================================
bool PresetManager::getIsCurrentPresetSaved()
{
    return mCurrentPresetIsSaved;
}

juce::String PresetManager::getCurrentPresetName()
{
    return mCurrentPresetName;
}

//==============================================================================
void PresetManager::storeLocalPreset()
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
