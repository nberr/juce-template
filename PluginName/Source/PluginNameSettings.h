/*
  ==============================================================================

    PluginNameSettings.h
    Created: 10 Jan 2022 1:19:26pm
    Author:  Nicholas Berriochoa

  ==============================================================================
*/

#pragma once

//==============================================================================
class PluginNameSettings {
public:
    //==============================================================================
    enum Settings {
        PNS_GUIScale = 0,
        PNS_showSidePanel,
        PNS_showHoverTips,
        PNS_defaultPresetIndex,
        PNS_TotalNumSettings
    };
    
    //==============================================================================
    inline static const juce::String IDs[PNS_TotalNumSettings] =
    {
        "GUIScale",
        "showSidePanel",
        "showHoverTips",
        "defaultPresetIndex"
    };
    
    inline static const juce::var Values[PNS_TotalNumSettings] =
    {
        1.0,
        false,
        true,
        0
    };
    
    inline static bool showSidePanel;
};
