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
parameters(*this, nullptr, "PARAMETERS", createParameterLayout()),
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
        // auto* channelData = buffer.getWritePointer (channel);

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
    juce::AudioProcessorValueTreeState::ParameterLayout params;
    
    for (int i = 0; i < PNP_TotalNumParameters; i++)
    {
        switch(PluginNameParameterTypes[i])
        {
            case is_int:
                params.add(std::make_unique<juce::AudioParameterInt>(PluginNameParameterID[i],
                                                                     PluginNameParameterName[i],
                                                                     PluginNameParameterMin[i].ivalue,
                                                                     PluginNameParameterMax[i].ivalue,
                                                                     PluginNameParameterDefault[i].ivalue,
                                                                     PluginNameParameterLabel[i]));
                break;
            case is_float:
                params.add(std::make_unique<juce::AudioParameterFloat>(PluginNameParameterID[i],
                                                                       PluginNameParameterName[i],
                                                                       juce::NormalisableRange<float>(PluginNameParameterMin[i].fvalue, PluginNameParameterMax[i].fvalue),
                                                                       PluginNameParameterDefault[i].fvalue,
                                                                       PluginNameParameterLabel[i]));
                break;
            case is_bool:
                params.add(std::make_unique<juce::AudioParameterBool>(PluginNameParameterID[i],
                                                                      PluginNameParameterName[i],
                                                                      PluginNameParameterDefault[i].bvalue,
                                                                      PluginNameParameterLabel[i]));
                break;
            case is_choice:
                params.add(std::make_unique<juce::AudioParameterChoice>(PluginNameParameterID[i],
                                                                        PluginNameParameterName[i],
                                                                        PluginNameParameterChoices[i],
                                                                        PluginNameParameterDefault[i].ivalue,
                                                                        PluginNameParameterLabel[i]));
                break;
        }
    }
    
    return params;
}
