//
//  BaseSequencer.hpp
//  JuceBasicAudio
//
//  Created by David Flores on 24/11/2016.
//
//

#ifndef BaseSequencer_hpp
#define BaseSequencer_hpp

/**
 Base Class that contains the main function of the sequencers, enables to load files and assign files as the pure virtual functions. Inherits from audio source and takes care of all those processes as well as allowing the sequencers to be solo or muted.
 
 @see Sequencer, MelodySequencer
 */

#include <stdio.h>
#include "../../JuceLibraryCode/JuceHeader.h"

class BaseSequencer :   public AudioSource
{
public:
    /** constructor */
    BaseSequencer();
    
    /** destructor */
    ~BaseSequencer();
    
    /** starts playing if newState = true */
    void setPlaying (bool newState);
    
    /** returns true if its playing */
    bool isPlaying()const;
    
    /** loads a file depending on its ID */
    void loadFile (const File& newFile);
        
    /** assigns the ID and corresponding file for the sequencer */
    virtual void assignID(int newSequencerID) = 0;
    
    /** in this function retrieve the directory sent from MixerUI and assign to each sequencer depending on its ID the file that it needs
     @see loadFile()*/
    virtual void setFile(File* file) = 0;
    
    /** mutes the sequencer */
    void mute();
    
    /** unmutes the sequencer */
    void unmute();
    
    /** returns true if sequencer is muted */
    bool isMuted()  { return muteState; }
    
    /** if another sequencer is solo it is important to use this function so that this component is muted without affecting the overall structure of this sequencer */
    void mutedBecauseOfSolo();
    
    /** if this sequencer was mutedBecauseOfSolo() it is important to unmute using this function */
    void unmuteSolo();
    
    /** sets a new gain for the sequencer */
    void changeGain(float newGain) { gain = newGain; audioTransportSource.setGain(gain); }
        
    // audioSource functions
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    
    void releaseResources() override;
    
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override;
    
private:
    AudioFormatReaderSource* currentAudioFileSource;
    AudioTransportSource audioTransportSource;
    
    bool muteState;
    bool muteBecauseOfSolo;
    
    int sequencerID;
    
    float gain;
};

#endif /* BaseSequencer_hpp */
