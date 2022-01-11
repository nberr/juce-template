/*
  ==============================================================================

    InterfaceDefines.h
    Created: 25 Nov 2021 8:56:01am
    Author:  Nicholas Berriochoa

  ==============================================================================
*/

#pragma once

class PluginNameGUI {
public:
    static constexpr float ratio = 1.618; // golden ratio
    static constexpr int height = 400,
                         width = height * ratio;
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

class MenuPanelGUI {
public:
    static constexpr int width = PluginNameGUI::width * 0.13f,
                         height = PluginNameGUI::height;
};

class PresetPanelGUI {
public:
    static constexpr int width = PluginNameGUI::width - MenuPanelGUI::width,
                         height = PluginNameGUI::height * 0.07f;
    
    static constexpr int undo_redo_width = 20,
                         undo_redo_height = undo_redo_width;
    
    static constexpr int change_preset_width = 20,
                         change_preset_height = change_preset_width;
    
    static constexpr int preset_display_width = 100,
                         preset_display_height = height * 0.5f;
    
    static constexpr int A_B_Copy_width = 20,
                         A_B_Copy_height = A_B_Copy_width;
};

class PresetOverlayGUI {
public:
    static constexpr int width = PluginNameGUI::width - MenuPanelGUI::width,
                         height = PluginNameGUI::height;
};


class MainPanelGUI {
public:
    static constexpr int width = PluginNameGUI::width - MenuPanelGUI::width,
                         height = PluginNameGUI::height - PresetPanelGUI::height;
    
};

class SidePanelGUI {
public:
    static constexpr int width = PluginNameGUI::width - PluginNameGUI::height,
                         height = PluginNameGUI::height;
    
};

