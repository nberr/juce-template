/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

#include "PluginNameParameters.h"

//==============================================================================
PluginNameAudioProcessor::PluginNameAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ),
#endif

parameters(*this, &undoManager, "PARAMETERS", createParameterLayout()),
mPresetManager(this, internalParameters.mPresetPath)
{
    
}

PluginNameAudioProcessor::~PluginNameAudioProcessor()
{
}

//==============================================================================
const juce::String PluginNameAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool PluginNameAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool PluginNameAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool PluginNameAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double PluginNameAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int PluginNameAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int PluginNameAudioProcessor::getCurrentProgram()
{
    return 0;
}

void PluginNameAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String PluginNameAudioProcessor::getProgramName (int index)
{
    return {};
}

void PluginNameAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void PluginNameAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void PluginNameAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool PluginNameAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void PluginNameAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        //auto* channelData = buffer.getWritePointer (channel);
        // ..do something to the data...
        
    }
}

//==============================================================================
bool PluginNameAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* PluginNameAudioProcessor::createEditor()
{
    return new PluginNameAudioProcessorEditor (*this);
}

//==============================================================================
void PluginNameAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    auto state = parameters.copyState();
    std::unique_ptr<juce::XmlElement> xml (state.createXml());
    
    // internal params
    xml->setAttribute("GUIScale", internalParameters.mGUIScale);
    
    copyXmlToBinary (*xml, destData);
}

void PluginNameAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    std::unique_ptr<juce::XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));
        
    if (xmlState.get() != nullptr) {
        if (xmlState->hasTagName (parameters.state.getType())) {
            parameters.replaceState (juce::ValueTree::fromXml (*xmlState));
        }
        
        internalParameters.mGUIScale = xmlState->getDoubleAttribute("GUIScale");
    }
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PluginNameAudioProcessor();
}

PluginNamePresetManager*  PluginNameAudioProcessor::getPresetManager()
{
    return &mPresetManager;
}

juce::AudioProcessorValueTreeState::ParameterLayout PluginNameAudioProcessor::createParameterLayout()
{
    juce::AudioProcessorValueTreeState::ParameterLayout layout;
    
    for (int i = 0; i < PluginNameParameters::PNP_TotalNumParameters; i++) {
        switch(PluginNameParameters::Types[i]) {
            case PluginNameParameters::is_int:
                layout.add(std::make_unique<juce::AudioParameterInt>(PluginNameParameters::IDs[i],
                                                                     PluginNameParameters::Names[i],
                                                                     PluginNameParameters::Mins[i].ivalue,
                                                                     PluginNameParameters::Maxs[i].ivalue,
                                                                     PluginNameParameters::Defaults[i].ivalue,
                                                                     PluginNameParameters::Labels[i]));
                break;
            case PluginNameParameters::is_float:
                layout.add(std::make_unique<juce::AudioParameterFloat>(PluginNameParameters::IDs[i],
                                                                       PluginNameParameters::Names[i],
                                                                                       juce::NormalisableRange<float>(PluginNameParameters::Mins[i].fvalue, PluginNameParameters::Maxs[i].fvalue),
                                                                       PluginNameParameters::Defaults[i].fvalue,
                                                                       PluginNameParameters::Labels[i]));
                break;
            case PluginNameParameters::is_bool:
                layout.add(std::make_unique<juce::AudioParameterBool>(PluginNameParameters::IDs[i],
                                                                      PluginNameParameters::Names[i],
                                                                      PluginNameParameters::Defaults[i].bvalue,
                                                                      PluginNameParameters::Labels[i]));
                break;
            case PluginNameParameters::is_choice:
                layout.add(std::make_unique<juce::AudioParameterChoice>(PluginNameParameters::IDs[i],
                                                                        PluginNameParameters::Names[i],
                                                                        PluginNameParameters::Choices[i],
                                                                        PluginNameParameters::Defaults[i].ivalue,
                                                                        PluginNameParameters::Labels[i]));
                break;
                
        }
    }
    
    return layout;
}
