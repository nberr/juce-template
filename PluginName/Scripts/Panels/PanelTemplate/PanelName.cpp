#include "PanelName.h"

//==============================================================================
PanelName::PanelName(PluginNameAudioProcessor* processor)
:   PanelBase(processor)
{
    setName("PanelName");
    setComponentID("PanelNameID");
}

PanelName::~PanelName()
{
    
}

//==============================================================================
void PanelName::resized()
{
    
}
