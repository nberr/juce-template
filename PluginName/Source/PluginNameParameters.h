/*
  ==============================================================================

    PluginNameParameters.h
    Created: 25 Nov 2021 9:01:33am
    Author:  Nicholas Berriochoa

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
class PluginNameParameters {
public:
    //==============================================================================
    enum Parameters {
        // PNP_MasterOnOff,
        PNP_Int = 0,
        PNP_Float,
        PNP_Bool,
        PNP_Choice,
        PNP_TotalNumParameters
    };
    
    //==============================================================================
    typedef enum type_t {
        is_int,
        is_float,
        is_bool,
        is_choice
    } type;
    
    inline static type Types[PNP_TotalNumParameters] = {
        is_int,
        is_float,
        is_bool,
        is_choice
    };
    
    //==============================================================================
    inline static const juce::var Defaults[PNP_TotalNumParameters] = {
        1,
        1.0,
        false,
        2
    };
    
    inline static const juce::var Mins[PNP_TotalNumParameters] = {
        0,
        0.0,
        false,
        0
    };

    inline static const juce::var Maxs[PNP_TotalNumParameters] = {
        10,
        1.0,
        true,
        3
    };
    
    inline static const juce::StringArray Choices[PNP_TotalNumParameters]  = {
        juce::StringArray(),
        juce::StringArray(),
        juce::StringArray(),
        juce::StringArray("choice 1", "choice 2")
    };

    //==============================================================================
    inline static const juce::String IDs[PNP_TotalNumParameters] =
    {
        "Int",
        "Float",
        "Bool",
        "Choice"
    };

    inline static const juce::String Names[PNP_TotalNumParameters] =
    {
        "Int",
        "Float",
        "Bool",
        "Choice"
    };

    inline static const juce::String Labels[PNP_TotalNumParameters] =
    {
        "Int",
        "Float",
        "Bool",
        "Choice"
    };
};
