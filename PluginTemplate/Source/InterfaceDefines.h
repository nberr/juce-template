/*
  ==============================================================================

    InterfaceDefines.h
    Created: 12 Apr 2021 5:03:28pm
    Author:  Nicholas Berriochoa

  ==============================================================================
*/

#pragma once

class PluginNameGUI {
public:
    
    class Scale {
    public:
        static constexpr float small = 0.8f,
        normal = 1.0f,
        large = 1.2f,
        extra_large = 1.4f,
        XXL = 2.0f;
    };
    
    static constexpr int corner_size = 1, line_thickness = 1;
};

class MainPanelGUI {
public:
    static constexpr int width = 400,
                         height = 300;
    
};

class PresetPanelGUI {
public:
    static constexpr int width = MainPanelGUI::width,
                         height = MainPanelGUI::height * 0.15f;
    
    static constexpr int preset_display_width = width / 3.0f,
                         preset_display_height = height * 0.5f;
    
    static constexpr int change_preset_width = height * 0.5f,
                         change_preset_height = height * 0.5f;
};

class PresetOverlayGUI {
public:
    static constexpr int width = MainPanelGUI::width,
                         height = MainPanelGUI::height - PresetPanelGUI::height;
    
    static constexpr int button_width = PresetPanelGUI::change_preset_width,
                         button_height = button_width;
    class SavePresetGUI
    {
    public:
        static constexpr int button_width = PresetPanelGUI::change_preset_width,
                             button_height = button_width;
    };
};

