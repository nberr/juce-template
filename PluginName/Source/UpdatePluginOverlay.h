/*
  ==============================================================================

    UpdatePluginOverlay.h
    Created: 7 Feb 2022 9:11:19am
    Author:  Nicholas Berriochoa

  ==============================================================================
*/

#pragma once

#include "OverlayBase.h"

class UpdatePluginOverlay
:   public OverlayBase
{
public:
    //==============================================================================
    UpdatePluginOverlay(PluginNameAudioProcessor* inProcessor, ContextMenu* inContextMenu);
    ~UpdatePluginOverlay() override;
    
    //==============================================================================
    void resized() override;
    
private:
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (UpdatePluginOverlay)
};
