/*
  ==============================================================================

    PresetManager.cpp
    Created: 25 Nov 2021 9:02:19am
    Author:  Nicholas Berriochoa

  ==============================================================================
*/

#include "PresetManager.h"

//==============================================================================
PresetManager::PresetManager(juce::AudioProcessor* processor, juce::AudioProcessorValueTreeState* parameters)
:   processor(processor),
    parameters(parameters)
{
    // create the plugin directory
    if (!juce::File(pluginDirectory).exists()) {
        // create the preset directory
        if(juce::File(pluginDirectory).createDirectory().fail("Failed to create preset directory")) {
            jassertfalse;
        }
    }
    
    rootViewItem = new PresetViewItem("root", "", false, true);
    //userPresets = new PresetViewItem("User", "", false, true);
    
    //rootViewItem->addSubItem(userPresets);
    
    // Configure the preset view
    rootViewItem->setOpen(true);
    
    // populate the factory presets
    populateFactoryPresets(factoryPresets);
    
    for (PresetViewItem *item : factoryPresets) {
        rootViewItem->addSubItem(item);
    }
    
    if (presetsFile.exists()) {
        // try to load the file into the tree
        std::unique_ptr<juce::XmlElement> xml = juce::XmlDocument(presetsFile).getDocumentElement();
        
        presetsTree = juce::ValueTree::fromXml(*xml);
        
        // tree didn't load properly. maybe bad xml?
        if (!presetsTree.isValid()) {
            jassertfalse;
        }
        
        userPresets = new PresetViewItem("User", "", false, true);
        
        populateUserPresets(userPresets);
        
        if (userPresets->getNumSubItems() > 0) {
            rootViewItem->addSubItem(userPresets, 0);
        }
    }
    
    processor->getStateInformation(presetA);
    processor->getStateInformation(presetB);
}

PresetManager::~PresetManager()
{
    
}

//==============================================================================
void PresetManager::savePreset(juce::String name, juce::String notes, bool shouldBeDefault)
{
    // presetManager should handle
    // 1. saving the preset to the xml file
    // 2. adding the preset to the PresetViewTree
    // user hasn't saved presets before
    if (!presetsFile.exists()) {
        // initialize the tree
        presetsTree = juce::ValueTree(juce::Identifier("Preset"));
        
        // create presetsFile and check for errors
        if(presetsFile.create().fail("Failed to create presetFile")) {
            jassertfalse;
        }
        
        userPresets = new PresetViewItem("User", "", false, true);
    }
    
    // add new preset to the tree and rewrite the file
    juce::ValueTree presetTree = juce::ValueTree(juce::Identifier("Preset"));
    
    // set the preset properties
    presetTree.setProperty(juce::Identifier("name"), name, nullptr);
    presetTree.setProperty(juce::Identifier("notes"), notes, nullptr);
    presetTree.setProperty(juce::Identifier("url"), JucePlugin_ManufacturerWebsite, nullptr);
    presetTree.setProperty(juce::Identifier("uuid"), juce::Uuid().toDashedString(), nullptr);
    
    // copy parameter state to a ValueTree and add it to the preset
    juce::ValueTree parameterTree = parameters->copyState();
    presetTree.appendChild(parameterTree, nullptr);
    
    // add the preset to the presetsTree
    presetsTree.appendChild(presetTree, nullptr);
    
    // create the xml and write the file
    std::unique_ptr<juce::XmlElement> xml = presetsTree.createXml();
    if (!xml->writeTo(presetsFile)) {
        jassertfalse;
    }
    
    if (userPresets->getNumSubItems() == 0) {
        rootViewItem->addSubItem(userPresets, 0);
    }
    
    PresetViewItem *newPreset = new PresetViewItem(name, notes, shouldBeDefault, false);
    userPresets->setSelected(false, true);
    newPreset->setSelected(true, true);
    userPresets->addSubItem(newPreset);
}

void PresetManager::updatePreset(juce::String name)
{
    
}

void PresetManager::loadPreset(juce::String name)
{
    
}

//==============================================================================
void PresetManager::populateUserPresets(PresetViewItem* userPresets)
{
    std::unique_ptr<juce::XmlElement> xml = juce::XmlDocument(presetsFile).getDocumentElement();
    
    for (auto* preset : xml->getChildIterator()) {
        juce::String presetName = preset->getStringAttribute("name");
        juce::String presetNotes = preset->getStringAttribute("notes");
        
        userPresets->addSubItem(new PresetViewItem(presetName, presetNotes, false, false));
    }
}

void PresetManager::populateFactoryPresets(std::vector<PresetViewItem *>& factoryPresets)
{
    // parse xml from binary data
    std::unique_ptr<juce::XmlElement> xml = juce::parseXML(BinaryData::FactoryPresets_xml);
    
    // for each group in the xml file
    for (auto* group : xml->getChildIterator()) {
        
        // create a group
        juce::String groupName = group->getStringAttribute("name");
        PresetViewItem *groupItem = new PresetViewItem(groupName, "", false, true);
        
        // for each preset in the group
        // add it to the tree
        for (auto* preset : group->getChildIterator()) {
            juce::String presetName = preset->getStringAttribute("name");
            juce::String presetNotes = preset->getStringAttribute("notes");

            groupItem->addSubItem(new PresetViewItem(presetName, presetNotes, false, false));
        }
        
        // push the tree to the vector to be used by the display
        factoryPresets.push_back(groupItem);
    }
}

PresetViewItem* PresetManager::getRootItem()
{
    return rootViewItem;
}

//==============================================================================
void PresetManager::updateQuickPreset()
{
    // if this function was called from toggling the presets, exit.
    // this is necessary because calling toggleQuickPreset triggers
    // the listener for comboBoxChanged and sliderValueChanged which
    // then calls this function. This doesn't and shouldn't be done
    // so this boolean protects that from happening
    if (fromToggle) {
        DBG("From toggle");
        return;
    }
    
    switch (quickPresetInUse) {
        case QuickPreset::Preset_A:
            
            DBG("Updated A");
            processor->getStateInformation(presetA);
            
            break;
        case QuickPreset::Preset_B:
            
            DBG("Updated B");
            processor->getStateInformation(presetB);
            
            break;
        default:
            jassertfalse;
    }
    
    fromToggle = false;
}

void PresetManager::toggleQuickPreset()
{
    fromToggle = true;
    
    switch (quickPresetInUse) {
        case QuickPreset::Preset_A:
            DBG("Swapped from A to B");
            // change the current preset and load the data
            quickPresetInUse = QuickPreset::Preset_B;
            processor->setStateInformation(presetB.getData(), (int)presetB.getSize());
            
            break;
        case QuickPreset::Preset_B:
            DBG("Swapped from B to A");
            // change the current preset and load the data
            quickPresetInUse = QuickPreset::Preset_A;
            processor->setStateInformation(presetA.getData(), (int)presetA.getSize());
            
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
