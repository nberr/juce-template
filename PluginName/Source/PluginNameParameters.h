/*
  ==============================================================================

    PluginNameParameters.h
    Created: 25 Nov 2021 9:01:33am
    Author:  Nicholas Berriochoa

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class PluginNameParameters {
public:
    enum Parameters {
        PNP_Int = 0,
        PNP_Float,
        PNP_Bool,
        PNP_Choice,
        PNP_TotalNumParameters
    };
    
    typedef enum type_t {
        is_int,
        is_float,
        is_bool,
        is_choice
    } type;

    typedef union value_t {
        int ivalue;
        float fvalue;
        bool bvalue;
        int cvalue;
    } value;
    
    inline static const juce::StringArray Choices[PNP_TotalNumParameters]  = {
        juce::StringArray(),
        juce::StringArray(),
        juce::StringArray(),
        juce::StringArray("choice 1", "choice 2")
    };

    inline static type Types[PNP_TotalNumParameters] = {
        is_int,
        is_float,
        is_bool,
        is_choice
    };

    inline static const value Defaults[PNP_TotalNumParameters] = {
        {.ivalue = 1},
        {.fvalue = 1.0},
        {.bvalue = false},
        {.cvalue = 2}
    };

    inline static const value Mins[PNP_TotalNumParameters] = {
        {.ivalue = 0},
        {.fvalue = 0.0},
        {.bvalue = false},
        {.cvalue = 0}
    };

    inline static const value Maxs[PNP_TotalNumParameters] = {
        {.ivalue = 10},
        {.fvalue = 1.0},
        {.bvalue = true},
        {.cvalue = 3}
    };

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
