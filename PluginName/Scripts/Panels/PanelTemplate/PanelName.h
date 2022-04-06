#include "PanelBase.h"

//==============================================================================
class PanelName
:   public PanelBase
{
public:
    //==============================================================================
    PanelName(PluginNameAudioProcessor* processor);
    ~PanelName();
    
    //==============================================================================
    void resized() override;
    
private:
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PanelName)
};
