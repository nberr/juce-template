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

 name:             Unlocker
 version:          1.0.0
 vendor:           JUCE
 website:          http://juce.com
 description:      Generates key files for plugin unlocking.

 dependencies:     juce_core, juce_cryptography, juce_data_structures,
                   juce_events, juce_graphics, juce_gui_basics,
                   juce_product_unlocking
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

    if (args.size() != 5)
    {
        std::cout << "Requires 5 arguments: app-name user-email username machine-numbers private-key" << std::endl
                  << "  app-name:         name of the product being unlocked" << std::endl
                  << "  user-email:       user's email address" << std::endl
                  << "  username:         name of the user. Careful not to allow any spaces!" << std::endl
                  << "  machine-numbers:  a comma- or semicolon-separated list of all machine ID strings this user can run this product on (no whitespace between items!)" << std::endl
                  << "  private-key:      the RSA private key corresponding to the public key you've used in the app" << std::endl
                  << std::endl;

        return 1;
    }

    if (! args[4].containsChar (','))
    {
        std::cout << "Not a valid RSA key!" << std::endl;
        return 1;
    }

//! [Unlocker]
    // args[0]: app-name
    // args[1]: user-email
    // args[2]: username
    // args[3]: machine-numbers
    // args[4]: private-key

    std::cout << juce::KeyGeneration::generateKeyFile (args[0], args[1], args[2], args[3], juce::RSAKey (args[4])) << std::endl;
//! [Unlocker]
    return 0;
}
