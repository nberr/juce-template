/*
  ==============================================================================

    TemplateEffect.h
    Created: 25 Feb 2021 12:35:47pm
    Author:  Nicholas Berriochoa

  ==============================================================================
*/

#pragma once

class TemplateEffect
{
public:
    TemplateEffect();
    ~TemplateEffect();
    
    void process(float* inAudio, float inGain, float* outAudio, int inNumSamplesToRender);
    
    
    
private:
    
};
