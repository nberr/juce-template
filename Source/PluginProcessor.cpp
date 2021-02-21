/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

#include "TemplateParameters.h"

//==============================================================================
Template_AudioProcessor::Template_AudioProcessor()
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
parameters(*this, nullptr, "PARAMETERS", createParameterLayout())
{
}

Template_AudioProcessor::~Template_AudioProcessor()
{
}

//==============================================================================
const juce::String Template_AudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool Template_AudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool Template_AudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool Template_AudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double Template_AudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int Template_AudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int Template_AudioProcessor::getCurrentProgram()
{
    return 0;
}

void Template_AudioProcessor::setCurrentProgram (int index)
{
}

const juce::String Template_AudioProcessor::getProgramName (int index)
{
    return {};
}

void Template_AudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void Template_AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void Template_AudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool Template_AudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void Template_AudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
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
        auto* channelData = buffer.getWritePointer (channel);

        // ..do something to the data...
    }
}

//==============================================================================
bool Template_AudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* Template_AudioProcessor::createEditor()
{
    return new Template_AudioProcessorEditor (*this);
}

//==============================================================================
void Template_AudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void Template_AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Template_AudioProcessor();
}

juce::AudioProcessorValueTreeState::ParameterLayout Template_AudioProcessor::createParameterLayout()
{
    juce::AudioProcessorValueTreeState::ParameterLayout params;
    
    for (int i = 0; i < TP_TotalNumParameters; i++)
    {
        switch(TemplateParameterTypes[i])
        {
            case is_int:
                params.add(std::make_unique<juce::AudioParameterInt>(TemplateParameterID[i],
                                                                     TemplateParameterName[i],
                                                                     TemplateParameterMin[i].ivalue,
                                                                     TemplateParameterMax[i].ivalue,
                                                                     TemplateParameterDefault[i].ivalue,
                                                                     TemplateParameterLabel[i]));
                break;
            case is_float:
                params.add(std::make_unique<juce::AudioParameterFloat>(TemplateParameterID[i],
                                                                       TemplateParameterName[i],
                                                                       juce::NormalisableRange<float>(TemplateParameterMin[i].fvalue, TemplateParameterMax[i].fvalue),
                                                                       TemplateParameterDefault[i].fvalue,
                                                                       TemplateParameterLabel[i]));
                break;
            case is_bool:
                params.add(std::make_unique<juce::AudioParameterBool>(TemplateParameterID[i],
                                                                      TemplateParameterName[i],
                                                                      TemplateParameterDefault[i].bvalue,
                                                                      TemplateParameterLabel[i]));
                break;
            case is_choice:
                params.add(std::make_unique<juce::AudioParameterChoice>(TemplateParameterID[i],
                                                                        TemplateParameterName[i],
                                                                        TemplateParameterChoices[i],
                                                                        TemplateParameterDefault[i].ivalue,
                                                                        TemplateParameterLabel[i]));
                break;
        }
    }
    
    return params;
}
