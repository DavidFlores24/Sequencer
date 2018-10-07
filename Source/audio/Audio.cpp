/*
  ==============================================================================

    Audio.cpp
    Created: 13 Nov 2014 8:14:40am
    Author:  Tom Mitchell

  ==============================================================================
*/

#include "Audio.h"

Audio::Audio()
{
    audioDeviceManager.initialiseWithDefaultDevices (2, 2); //2 inputs, 2 outputs
    
    for (int i = 0; i<numOfSequencers; i++)
    {
        mixer.addInputSource(&sequencers[i], false);
    }
    
    for (int i = 0; i<numOfMelodySeqs; i++)
        mixer.addInputSource(&melodySeqs[i], false);
    
    audioSourcePlayer.setSource(&mixer);
    audioDeviceManager.addAudioCallback (this);
    
    bufferPos = 0;
    outputBuffer.setSize(2, bufferSize);
    outputBuffer.clear();
    
    recordState = false;
}

Audio::~Audio()
{    
    for(int i = 0; i<numOfSequencers; i++)
    {
        if(&sequencers[i] != nullptr)
            mixer.removeInputSource(&sequencers[i]);
    }

    for(int i = 0; i<numOfMelodySeqs; i++)
    {
        if(&melodySeqs[i] != nullptr)
            mixer.removeInputSource(&melodySeqs[i]);
    }
    
    audioDeviceManager.removeAudioCallback(this);
}

void Audio::audioDeviceIOCallback (const float** inputChannelData,
                                           int numInputChannels,
                                           float** outputChannelData,
                                           int numOutputChannels,
                                           int numSamples)
{
    audioSourcePlayer.audioDeviceIOCallback(inputChannelData, numInputChannels, outputChannelData, numOutputChannels, numSamples);
    
    //All audio processing is done here
    const float *inL = inputChannelData[0];
    const float *inR = inputChannelData[1];
    float *outL = outputChannelData[0];
    float *outR = outputChannelData[1];
    
    float inSampL;
    float inSampR;
    
    while(numSamples--)
    {
        inSampL = *outL;
        inSampR = *outR;
        
        *outL = inSampL * 1.f;
        *outR = inSampR * 1.f;
        
        float outputL = *outL;
        float outputR = *outR;
        
        if(recordState) // if the user has requested to record, recordState will be true for 30secs
        {
            float *bufferSampleL = outputBuffer.getWritePointer(0, bufferPos);  // get pointers to each channel of our currently empty buffer
            float *bufferSampleR = outputBuffer.getWritePointer(1, bufferPos);
            
            *bufferSampleL = outputL;   // assign the current values to each pointer
            *bufferSampleR = outputR;
            
            bufferPos++;                // update the bufferPosition
            
            if(bufferPos == bufferSize) // if we have reached the buffer limit then stop recording and alert the listeners
            {
                bufferPos = 0;
                sendChangeMessage();
                recordButtonPressed(false);
            }
        }
        inL++;
        inR++;
        outL++;
        outR++;
    }
}


void Audio::audioDeviceAboutToStart (AudioIODevice* device)
{
    audioSourcePlayer.audioDeviceAboutToStart(device);
}

void Audio::audioDeviceStopped()
{
    audioSourcePlayer.audioDeviceStopped();
}


