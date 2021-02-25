/*
  ==============================================================================

    TemplatePresetManager.cpp
    Created: 25 Feb 2021 3:41:57pm
    Author:  Nicholas Berriochoa

  ==============================================================================
*/

#include "TemplatePresetManager.h"

#include "TemplateParameters.h"

#if JUCE_WINDOWS
    #define DIR_SEP "\\"
#elseif JUCE_MAC
    #define DIR_SEP "/"
#else
    #define DIR_SEP "/"
#endif


TemplatePresetManager::TemplatePresetManager(juce::AudioProcessor* inProcssor)
:   mCurrentPresetIsSaved(false),
    mCurrentPresetName("Untitled"),
    mProcessor(inProcssor)
{
    const juce::String pluginName = (juce::String)mProcessor->getName();
    mPresetDirectory = juce::File::getSpecialLocation(juce::File::userHomeDirectory).getFullPathName() + DIR_SEP + pluginName;
    
    if (!juce::File(mPresetDirectory).exists())
    {
        juce::File(mPresetDirectory).createDirectory();
    }
    
    storeLocalPreset();
}

TemplatePresetManager::~TemplatePresetManager()
{
    
}

void TemplatePresetManager::getXmlForPreset(juce::XmlElement* inElement)
{
    auto& parameters = mProcessor->getParameters();
    
    for (int i = 0; i < parameters.size(); i++)
    {
        juce::AudioProcessorParameterWithID* parameter = (juce::AudioProcessorParameterWithID*)parameters.getUnchecked(i);
        
        inElement->setAttribute(parameter->paramID, parameter->getValue());
    }
}

void TemplatePresetManager::loadPresetForXml(juce::XmlElement* inElement)
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

int TemplatePresetManager::getNumberOfPresets()
{
    return mLocalPresets.size();
}

juce::String TemplatePresetManager::getPresetName(int inPresetIndex)
{
    return mLocalPresets[inPresetIndex].getFileNameWithoutExtension();
}

void TemplatePresetManager::createNewPreset()
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

void TemplatePresetManager::savePreset()
{
    juce::MemoryBlock destinationData;
    mProcessor->getStateInformation(destinationData);
    
    mCurrentlyLoadedPreset.deleteFile();
    mCurrentlyLoadedPreset.appendData(destinationData.getData(),
                                      destinationData.getSize());
    
    mCurrentPresetIsSaved = true;
}

void TemplatePresetManager::saveAsPreset(juce::String inPresetName)
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

void TemplatePresetManager::loadPreset(int inPresetIndex)
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

bool TemplatePresetManager::getIsCurrentPresetSaved()
{
    return mCurrentPresetIsSaved;
}

juce::String TemplatePresetManager::getCurrentPresetName()
{
    return mCurrentPresetName;
}

void TemplatePresetManager::storeLocalPreset()
{
   /* mLocalPresets.clear();
    
    for (juce::RangedDirectoryIterator di (juce::File(mPresetDirectory),
                                           false,
                                           "*" + (juce::String)PRESET_FILE_EXTENSION,
                                           juce::File::TypesOfFileToFind::findFiles);
         ; di++)
    {
        juce::File preset = di->getFile();
        mLocalPresets.add(preset);
    }*/
}
