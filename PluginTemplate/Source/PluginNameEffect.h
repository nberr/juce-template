/*
  ==============================================================================

    PluginNameEffect.h
    Created: 12 Apr 2021 5:02:20pm
    Author:  Nicholas Berriochoa

  ==============================================================================
*/

#pragma once

class PluginNameEffect
{
public:
    PluginNameEffect();
    ~PluginNameEffect();
    
    void process(float* inAudio, float inGain, float* outAudio, int inNumSamplesToRender);
    
private:
    
};
