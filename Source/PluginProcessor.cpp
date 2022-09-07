/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
LePhonkAudioProcessor::LePhonkAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ),
    treeState(*this, nullptr, "PARAMETER", { createParameterLayout() })
#endif
{
    ott.setAtomics(treeState);
    fonz.setAtomics(treeState);
    zekete.setAtomics(treeState);
}

LePhonkAudioProcessor::~LePhonkAudioProcessor()
{
}

juce::AudioProcessorValueTreeState::ParameterLayout LePhonkAudioProcessor::createParameterLayout()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

    params.push_back(std::make_unique<juce::AudioParameterFloat>(OTT_ID,    OTT_NAME,     0.f, 100.f, 0.f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(FONZ_ID,   FONZ_NAME,    0.f, 100.f, 0.f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(ZEKETE_ID, ZEKETE_NAME,  0.f, 100.f, 0.f));

    return { params.begin(), params.end() };
}

//==============================================================================
const juce::String LePhonkAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool LePhonkAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool LePhonkAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool LePhonkAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double LePhonkAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int LePhonkAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int LePhonkAudioProcessor::getCurrentProgram()
{
    return 0;
}

void LePhonkAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String LePhonkAudioProcessor::getProgramName (int index)
{
    return {};
}

void LePhonkAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void LePhonkAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = getNumInputChannels();
    spec.sampleRate = sampleRate;

    zekete.prepare(spec);
    ott.prepare(spec);
    fonz.prepare(spec);

    ringBuffer.prepare(spec);
}

void LePhonkAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool LePhonkAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void LePhonkAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    auto audioBlock = juce::dsp::AudioBlock<float>(buffer).getSubsetChannelBlock(0, (size_t)totalNumInputChannels);
    auto context = juce::dsp::ProcessContextReplacing<float>(audioBlock);

    ringBuffer.writeSamples(audioBlock);
    zekete.process(context);
    ott.process(context);
    fonz.process(context);
}

//==============================================================================
bool LePhonkAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* LePhonkAudioProcessor::createEditor()
{
    return new LePhonkAudioProcessorEditor (*this);
}

//==============================================================================
void LePhonkAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    auto state = treeState.copyState();
    std::unique_ptr<juce::XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);
}

void LePhonkAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));

    // 'If' statements are for error checking
    if (xmlState != nullptr) {
        if (xmlState->hasTagName(treeState.state.getType())) {
            treeState.replaceState(juce::ValueTree::fromXml(*xmlState));
        }
    }
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new LePhonkAudioProcessor();
}
