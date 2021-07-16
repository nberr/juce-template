/*
  ==============================================================================

    PluginNameParameters.h
    Created: 12 Apr 2021 5:01:42pm
    Author:  Nicholas Berriochoa

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class PluginNameParameters {
public:
    
};

enum PluginNameParameter
{
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

static const juce::StringArray PluginNameParameterChoices[PNP_TotalNumParameters]  = {
    juce::StringArray(),
    juce::StringArray(),
    juce::StringArray(),
    juce::StringArray("choice 1", "choice 2")
};

static type PluginNameParameterTypes[PNP_TotalNumParameters] = {
    is_int,
    is_float,
    is_bool,
    is_choice
};

static const value PluginNameParameterDefault[PNP_TotalNumParameters] = {
    {.ivalue = 1},
    {.fvalue = 1.0},
    {.bvalue = false},
    {.cvalue = 2}
};

static const value PluginNameParameterMin[PNP_TotalNumParameters] = {
    {.ivalue = 0},
    {.fvalue = 0.0},
    {.bvalue = false},
    {.cvalue = 0}
};

static const value PluginNameParameterMax[PNP_TotalNumParameters] = {
    {.ivalue = 10},
    {.fvalue = 1.0},
    {.bvalue = true},
    {.cvalue = 3}
};

static const juce::String PluginNameParameterID[PNP_TotalNumParameters] =
{
    "Int",
    "Float",
    "Bool",
    "Choice"
};

static const juce::String PluginNameParameterName[PNP_TotalNumParameters] =
{
    "Int",
    "Float",
    "Bool",
    "Choice"
};

static const juce::String PluginNameParameterLabel[PNP_TotalNumParameters] =
{
    "Int",
    "Float",
    "Bool",
    "Choice"
};
