/*
  ==============================================================================

    PresetManager.cpp
    Created: 25 Nov 2021 9:02:19am
    Author:  Nicholas Berriochoa

  ==============================================================================
*/

#include "PresetManager.h"

//==============================================================================
PresetManager::PresetManager(juce::AudioProcessor* inProcssor, juce::AudioProcessorValueTreeState* inParameters)
:   mProcessor(inProcssor),
    parameters(inParameters),
    mCurrentPresetIsSaved(false),
    mCurrentPresetName("Untitled")
{
    juce::String dir_sep = juce::File::getSeparatorString();
    mPresetDirectory = juce::File::getSpecialLocation(juce::File::userMusicDirectory).getFullPathName()
                       + dir_sep + JucePlugin_Manufacturer
                       + dir_sep + JucePlugin_Name
                       + dir_sep + "Presets";
    
    
    if (!juce::File(mPresetDirectory).exists()) {
        
        // create the preset directory
        if(juce::File(mPresetDirectory).createDirectory().fail("Failed to create preset directory")) {
            jassertfalse;
        }
    }
    
    mProcessor->getStateInformation(presetA);
    mProcessor->getStateInformation(presetB);
    
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

juce::String PresetManager::getPresetPath()
{
    return mPresetDirectory;
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
    // path information
    juce::String dir_sep = juce::File::getSeparatorString();
    juce::File presetXML = juce::File(mPresetDirectory + dir_sep + inPresetName + PRESET_FILE_EXTENSION);
    
    // delete the preset file if it exists
    // save as overwrites the existing settings
    if (presetXML.exists()) {
        presetXML.deleteFile();
    }
    
    if (presetXML.create().fail("Failed to create xml file")) {
        jassertfalse;
    }
    
    // convert parameter state to xml and write to data to the file
    auto state = parameters->copyState();
    std::unique_ptr<juce::XmlElement> xml = state.createXml();
    xml->writeTo(presetXML);
    
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

//==============================================================================
void PresetManager::populateViewItem(PresetViewItem* item)
{
    if (item->isDirectory) {
        juce::File directory(mPresetDirectory);
        
        juce::Array<juce::File> presets = directory.findChildFiles(juce::File::TypesOfFileToFind::findFiles, false, "*.xml");
        
        for (juce::File f : presets) {
            item->addSubItem(new PresetViewItem(f.getFileName(), "", false, false));
        }
    }
}

//==============================================================================
void PresetManager::updateQuickPreset()
{
    switch (quickPresetInUse) {
        case QuickPreset::Preset_A:
            
            DBG("Updated A");
            mProcessor->getStateInformation(presetA);
            
            break;
        case QuickPreset::Preset_B:
            
            DBG("Updated B");
            mProcessor->getStateInformation(presetB);
            
            break;
        default:
            jassertfalse;
    }
}

void PresetManager::toggleQuickPreset()
{
    switch (quickPresetInUse) {
        case QuickPreset::Preset_A:
            DBG("Swapped from A to B");
            // change the current preset and load the data
            quickPresetInUse = QuickPreset::Preset_B;
            mProcessor->setStateInformation(presetB.getData(), (int)presetB.getSize());
            
            break;
        case QuickPreset::Preset_B:
            DBG("Swapped from B to A");
            // change the current preset and load the data
            quickPresetInUse = QuickPreset::Preset_A;
            mProcessor->setStateInformation(presetA.getData(), (int)presetA.getSize());
            
            break;
        default:
            jassertfalse;
    }
}

void PresetManager::copyQuickPreset()
{
    switch (quickPresetInUse) {
        case QuickPreset::Preset_A:
            DBG("Copying A to B");
            
            // change the current preset and copy it to the other
            quickPresetInUse = QuickPreset::Preset_B;
            presetA.copyTo(presetB.getData(), 0, presetB.getSize());
            
            break;
        case QuickPreset::Preset_B:
            DBG("Copying B to A");
            
            // change the current preset and copy it to the other
            quickPresetInUse = QuickPreset::Preset_A;
            presetB.copyTo(presetA.getData(), 0, presetA.getSize());
            
            break;
        default:
            jassertfalse;
    }
}
