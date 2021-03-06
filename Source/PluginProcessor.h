#ifndef PLUGINPROCESSOR_H_INCLUDED
#define PLUGINPROCESSOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "EnvelopeManager.h"

class FloatParameter;

//==============================================================================
/**
*/
class AlkamistSidechainCompressorAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    AlkamistSidechainCompressorAudioProcessor();
    ~AlkamistSidechainCompressorAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

    void processBlock (AudioSampleBuffer&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override                                                 { return true; };

    //==============================================================================
    const String getName() const override                                           { return JucePlugin_Name; }

    const String getInputChannelName (int channelIndex) const override;
    const String getOutputChannelName (int channelIndex) const override;
    bool isInputChannelStereoPair (int index) const override;
    bool isOutputChannelStereoPair (int index) const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool silenceInProducesSilenceOut() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override                                                   { return 1; }
    int getCurrentProgram() override                                                { return 0; }
    void setCurrentProgram (int /*index*/) override                                 {}
    const String getProgramName (int /*index*/) override                            { return "Default"; }
    void changeProgramName (int /*index*/, const String& /*newName*/) override      {}

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    //==============================================================================

    void reset (double inputSampleRate, int inputBlockSize);

    FloatParameter* holdLevel;
    FloatParameter* attackTime;
    FloatParameter* releaseTime;
    FloatParameter* attackBottomWeight;
    FloatParameter* attackTopWeight;
    FloatParameter* releaseBottomWeight;
    FloatParameter* releaseTopWeight;

private:

    void bufferParameters();
    void sendParameterBuffers();
    void clearParameterChanges();

    EnvelopeManager mEnvelopeManager;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AlkamistSidechainCompressorAudioProcessor)
};

#endif  // PLUGINPROCESSOR_H_INCLUDED
