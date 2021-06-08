/*
  ==============================================================================

    InterfaceDefines.h
    Created: 12 Apr 2021 5:03:28pm
    Author:  Nicholas Berriochoa

  ==============================================================================
*/

#pragma once

class GUI_Scale {
public:
    static constexpr float small = 0.8f,
    normal = 1.0f,
    large = 1.2f,
    extra_large = 1.4f,
    XXL = 2.0f;
};

class Panel_Size {
public:
    static constexpr int main_panel_width = 400,
                         main_panel_height = 300,
                         preset_panel_width = main_panel_width,
                         preset_panel_height = main_panel_height * 0.15;
    
    static constexpr int corner_size = 1, line_thickness = 1;
};

