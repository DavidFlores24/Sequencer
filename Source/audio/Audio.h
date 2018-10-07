/*
  ==============================================================================

    Audio.h
    Created: 13 Nov 2014 8:14:40am
    Author:  Tom Mitchell

  ==============================================================================
*/

#ifndef AUDIO_H_INCLUDED
#define AUDIO_H_INCLUDED

/**
 Class containing all audio processes
 @param outputBuffer this is the buffer that will be filled when the sequencer is recording
 */

#include "../../JuceLibraryCode/JuceHeader.h"
#include "../DrumSequencer/Sequencer.hpp"
#include "../MelodySequencer/Melody.hpp"

class Audio :   public AudioIODeviceCallback,
                public ChangeBroadcaster
{
public:
    /** Constructor */
    Audio();
    
    /** Destructor */
    ~Audio();
    
    /** Returns the audio device manager, don't keep a copy of it! */
    AudioDeviceManager& getAudioDeviceManager() { return audioDeviceManager;}
    
    Drum& getSequencer(int index) {return sequencers[index]; }
    
    MelodySequencer& getMelodySeq(int index) { return melodySeqs[index]; }
    
    void timerCalled();
    
    /** returns an audioBuffer, it is sent to the mainComponent to create the file if the user has requested to save
     @see MainComponent::record() */
    AudioSampleBuffer& getBufferToSave() {return outputBuffer; }
    
    /** call this function whenever the recordButton is pressed outside of this class */
    void recordButtonPressed(bool newRecordButtonState) { recordState = newRecordButtonState; }
    
    /** returns the recordState */
    bool recordingState() { return recordState; }
    
    void stop() { audioSourcePlayer.audioDeviceStopped(); }
        
    void audioDeviceIOCallback (const float** inputChannelData,
                                int numInputChannels,
                                float** outputChannelData,
                                int numOutputChannels,
                                int numSamples) override;
    
    void audioDeviceAboutToStart (AudioIODevice* device) override;
    
    void audioDeviceStopped() override;
private:
    static const int numOfSequencers = 4;
    static const int numOfMelodySeqs = 8;
    
    AudioDeviceManager audioDeviceManager;
    
    AudioSourcePlayer audioSourcePlayer;
    MixerAudioSource mixer;
    
    Drum sequencers[numOfSequencers];
    MelodySequencer melodySeqs[numOfMelodySeqs];
    
    AudioSampleBuffer outputBuffer;
    static const int bufferSize = 44100 * 30;
    unsigned int bufferPos;
        
    bool recordState;
};



#endif  // AUDIO_H_INCLUDED
