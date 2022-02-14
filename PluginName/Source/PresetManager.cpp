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
    
    // need to initialize three things
    // 1. ValueTree presetsTree; this is the connection between the
    //    presetManager and the .xml file
    // 2. PresetViewItem rootViewItem; this allows the presetDisplayOverlay to
    //    ... display the presets!
    // 3. std::vector<XmlElement> presetsXmlData; this contains the actual
    //    actual preset data that is needed to load and store values
    initializePresetsTree();
    initializeRootViewItem();
    initializePresetsXmlData();

    processor->getStateInformation(presetA);
    processor->getStateInformation(presetB);
}

PresetManager::~PresetManager()
{
    
}

//==============================================================================
void PresetManager::savePreset(juce::String name, juce::String notes, bool shouldBeDefault)
{
    // save the preset to the .xml file via the presetsTree
    // if the user hasn't saved presets before, do some setup
    if (!presetsFile.exists()) {
        // initialize the tree
        presetsTree = juce::ValueTree(juce::Identifier("Presets"));
        
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
    
    // add the preset to rootViewItem to be displayed
    if (userPresets->getNumSubItems() == 0) {
        rootViewItem->addSubItem(userPresets, 0);
    }
    
    // add the preset to the rootViewItem via userPresets
    PresetViewItem *newPreset = new PresetViewItem(name, notes, shouldBeDefault, false);
    userPresets->setSelected(false, true);
    newPreset->setSelected(true, true);
    userPresets->addSubItem(newPreset);
    
    // copy the xml to presetsXmlData
    presetsXmlData.insert(presetsXmlData.begin() + numUserPresets, *presetTree.createXml());
    currentPresetIndex = numUserPresets;
    numUserPresets++;
}

void PresetManager::updatePreset(juce::String name)
{
    
}

void PresetManager::loadPreset(juce::String name)
{
    if (name == currentPresetName) {
        return;
    }
    
    for (int i = 0; i < presetsXmlData.size(); i++) {
        
        juce::XmlElement xmlToLoad = presetsXmlData[i];
        
        if (xmlToLoad.getStringAttribute("name") == name) {
            
            // load the xml
            juce::MemoryBlock mb;
            processor->copyXmlToBinary(*xmlToLoad.getChildByName("PARAMETERS"), mb);
            processor->setStateInformation(mb.getData(), (int)mb.getSize());
            
            currentPresetIndex = i;
            currentPresetName = name;
            break;
        }
    }
}

void PresetManager::loadNextPreset()
{
    currentPresetIndex++;
    if (currentPresetIndex >= presetsXmlData.size()) {
        currentPresetIndex = 0;
    }
    
    juce::XmlElement presetToLoad = presetsXmlData[currentPresetIndex];
    loadPreset(presetToLoad.getStringAttribute("name"));
}

void PresetManager::loadPreviousPreset()
{
    currentPresetIndex--;
    if (currentPresetIndex < 0) {
        currentPresetIndex = (int)presetsXmlData.size() - 1;
    }
    
    juce::XmlElement presetToLoad = presetsXmlData[currentPresetIndex];
    loadPreset(presetToLoad.getStringAttribute("name"));
}

//==============================================================================
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
    
    fromToggle = false;
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

//==============================================================================
void PresetManager::initializePresetsTree()
{
    // only the user presets need to be loaded here because the PresetManager
    // might need to write to the file. on the other hand, the PresetManager
    // will never need write access to the factory presets file.
    
    // load user presets if they exist
    if (presetsFile.exists()) {
        // try to load the file into the tree
        std::unique_ptr<juce::XmlElement> xml = juce::XmlDocument(presetsFile).getDocumentElement();
        
        presetsTree = juce::ValueTree::fromXml(*xml);
        
        // tree didn't load properly. maybe bad xml?
        if (!presetsTree.isValid()) {
            jassertfalse;
        }
    }
}

//==============================================================================
void PresetManager::initializeRootViewItem()
{
    // both the user presets and the factory presets need to be loaded here
    // since the display needs to show both sets
    
    rootViewItem = new PresetViewItem("root", "", false, true);
    
    // Configure the preset view
    rootViewItem->setOpen(true);
    
    // populate the factory presets first
    populateFactoryPresets(factoryPresets);
    
    for (PresetViewItem *item : factoryPresets) {
        rootViewItem->addSubItem(item);
    }
    
    // prepend the user presets if they are valid
    if (presetsTree.isValid()) {
        userPresets = new PresetViewItem("User", "", false, true);
        populateUserPresets(userPresets);
        
        if (userPresets->getNumSubItems() > 0) {
            rootViewItem->addSubItem(userPresets, 0);
        }
    }
}

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

//==============================================================================
void PresetManager::initializePresetsXmlData()
{
    if (presetsFile.exists()) {
        // try to load the file into the tree
        std::unique_ptr<juce::XmlElement> xml = juce::XmlDocument(presetsFile).getDocumentElement();
        
        for (auto* preset : xml->getChildIterator()) {
            presetsXmlData.insert(presetsXmlData.begin() + numUserPresets, *preset);
            numUserPresets++;
        }
    }
    
    // parse xml from binary data
    std::unique_ptr<juce::XmlElement> xml = juce::parseXML(BinaryData::FactoryPresets_xml);
    
    // for each group in the xml file
    for (auto* group : xml->getChildIterator()) {
        for (auto* preset : group->getChildIterator()) {
            presetsXmlData.push_back(*preset);
        }
    }
}
