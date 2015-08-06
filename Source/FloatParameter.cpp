#include "PluginProcessor.h"

#include "FloatParameter.h"

FloatParameter::FloatParameter (AlkamistSidechainCompressorAudioProcessor* inputProcessor,
                                float defaultParameterValue,
                                float minimumParameterValue,
                                float maximumParameterValue,
                                const String& parameterName,
                                double inputSampleRate,
                                int inputBlockSize)
    : mParentProcessor (inputProcessor),
      mUnSmoothedParameterValue (defaultParameterValue),
      mDefaultValue (defaultParameterValue),
      mMinimumValue (minimumParameterValue),
      mMaximumValue (maximumParameterValue),
      mName (parameterName),
      mNormalizableRange (mMinimumValue, mMaximumValue),
      mLinearlySmoothedDouble (defaultParameterValue),
      mParameterChangeFlag (false)
{
    reset (inputSampleRate, inputBlockSize);
}

String FloatParameter::getText()
{
    float unNormalizedValue = mNormalizableRange.convertFrom0to1 (mUnSmoothedParameterValue);
    String outputString (unNormalizedValue);
    return outputString;
}

void FloatParameter::setValue (float inputValue)
{
    mUnSmoothedParameterValue = inputValue;
    mLinearlySmoothedDouble.setValue (inputValue);
    mParentProcessor->signalForParameterChange();
    this->mParameterChangeFlag = true;
}

float FloatParameter::getUnNormalizedSmoothedValue()
{
    float currentValue = (float) mLinearlySmoothedDouble.getCurrentValue();
    float unNormalizedValue = mNormalizableRange.convertFrom0to1 (currentValue);
    return unNormalizedValue;
}

float FloatParameter::getUnNormalizedUnSmoothedValue()
{
    float unNormalizedValue = mNormalizableRange.convertFrom0to1 (mUnSmoothedParameterValue);
    return unNormalizedValue;
}

float FloatParameter::getNormalizedSmoothedValue()
{
    return (float) mLinearlySmoothedDouble.getCurrentValue();
}

void FloatParameter::setNormalizedValue (float nonNormalizedValue)
{
    float newValue = mNormalizableRange.convertTo0to1 (nonNormalizedValue);
    this->setValueNotifyingHost (newValue);
}

void FloatParameter::processPerSample()
{
    mLinearlySmoothedDouble.processPerSample();
}

void FloatParameter::reset (double inputSampleRate, int inputBlockSize)
{
    // Linear Parameter Ramp
    double smoothingTimeInSeconds = ((double) inputBlockSize) / inputSampleRate;
    this->mLinearlySmoothedDouble.reset (inputSampleRate, smoothingTimeInSeconds);
}