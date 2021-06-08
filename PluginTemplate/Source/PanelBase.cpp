/*
  ==============================================================================

    PanelBase.cpp
    Created: 12 Apr 2021 5:02:48pm
    Author:  Nicholas Berriochoa

  ==============================================================================
*/

#include "PanelBase.h"

PanelBase::PanelBase(PluginNameAudioProcessor* inProcessor, ContextMenu* inContextMenu)
{
    mProcessor = inProcessor;
    mContextMenu = inContextMenu;
}

PanelBase::~PanelBase()
{
    
}

void PanelBase::paint(juce::Graphics& g)
{
    g.setColour(juce::Colours::white);
    g.fillAll();
    
    g.setColour(juce::Colours::black);
    g.drawRoundedRectangle(0, 0, getWidth(), getHeight(), Panel_Size::corner_size, Panel_Size::line_thickness);
}

void PanelBase::mouseDown(const juce::MouseEvent& event)
{
    bool rightClick = juce::ModifierKeys::getCurrentModifiers().isPopupMenu();
    
    if (rightClick) {
        mContextMenu->showMenu(getName());
        auto editor = findParentComponentOfClass<juce::AudioProcessorEditor>();
        editor->resized();
        resized();
        // how to trigger resize for all components
    }
}
