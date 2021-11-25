/*
  ==============================================================================

   This file is part of the JUCE tutorials.
   Copyright (c) 2020 - Raw Material Software Limited

   The code included in this file is provided under the terms of the ISC license
   http://www.isc.org/downloads/software-support-policy/isc-license. Permission
   To use, copy, modify, and/or distribute this software for any purpose with or
   without fee is hereby granted provided that the above copyright notice and
   this permission notice appear in all copies.

   THE SOFTWARE IS PROVIDED "AS IS" WITHOUT ANY WARRANTY, AND ALL WARRANTIES,
   WHETHER EXPRESSED OR IMPLIED, INCLUDING MERCHANTABILITY AND FITNESS FOR
   PURPOSE, ARE DISCLAIMED.

  ==============================================================================
*/

/*******************************************************************************
 The block below describes the properties of this PIP. A PIP is a short snippet
 of code that can be read by the Projucer and used to generate a JUCE project.

 BEGIN_JUCE_PIP_METADATA

 name:             KeyGenerator
 version:          1.0.0
 vendor:           JUCE
 website:          http://juce.com
 description:      Generates RSA key pairs for plugin unlocking.

 dependencies:     juce_core, juce_cryptography, juce_data_structures,
                   juce_events, juce_graphics, juce_gui_basics
 exporters:        xcode_mac, vs2019, linux_make

 type:             Console

 useLocalCopy:     1

 END_JUCE_PIP_METADATA

*******************************************************************************/


#pragma once

//==============================================================================
int main (int argc, char* argv[])
{
    juce::StringArray args;

    for (int i = 1; i < argc; ++i)
        args.add (argv[i]);

    if (args.size() != 0)
    {
        std::cout << "Requires no arguments" << std::endl
                  << std::endl;

        return 1;
    }

//! [KeyGenerator]
    juce::RSAKey publicKey;
    juce::RSAKey privateKey;

    juce::RSAKey::createKeyPair (publicKey, privateKey, 256);

    std::cout << "Public Key: "  << publicKey .toString() << std::endl
              << "Private Key: " << privateKey.toString() << std::endl
              << std::endl;
//! [KeyGenerator]

    return 0;
}
