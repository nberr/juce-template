/*
  ==============================================================================

    TemplateParameters.h
    Created: 21 Feb 2021 5:09:13pm
    Author:  Nicholas Berriochoa

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

enum TemplateParameter
{
    TP_Int = 0,
    TP_Float,
    TP_Bool,
    TP_Choice,
    TP_TotalNumParameters
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

static const juce::StringArray* TemplateParameterChoices[TP_TotalNumParameters]  = {
    NULL,
    NULL,
    NULL,
    new juce::StringArray("choice 1", "choice 2")
};

static type TemplateParameterTypes[TP_TotalNumParameters] = {
    is_int,
    is_float,
    is_bool,
    is_choice
};

static const value TemplateParameterDefault[TP_TotalNumParameters] = {
    {.ivalue = 1},
    {.fvalue = 1.0},
    {.bvalue = false},
    {.cvalue = 2}
};

static const value TemplateParameterMin[TP_TotalNumParameters] = {
    {.ivalue = 0},
    {.fvalue = 0.0},
    {.bvalue = false},
    {.cvalue = 0}
};

static const value TemplateParameterMax[TP_TotalNumParameters] = {
    {.ivalue = 10},
    {.fvalue = 1.0},
    {.bvalue = true},
    {.cvalue = 3}
};

static const juce::String TemplateParameterID[TP_TotalNumParameters] =
{
    "Int",
    "Float",
    "Bool",
    "Choice"
};

static const juce::String TemplateParameterName[TP_TotalNumParameters] =
{
    "Int",
    "Float",
    "Bool",
    "Choice"
};

static const juce::String TemplateParameterLabel[TP_TotalNumParameters] =
{
    "Int",
    "Float",
    "Bool",
    "Choice"
};
