//
//  MelodySequencerUI.hpp
//  JuceBasicAudio
//
//  Created by David Flores on 24/11/2016.
//
//

#ifndef MelodySequencerUI_hpp
#define MelodySequencerUI_hpp

/**
 MelodySequencerUI class, contains 8 MelodyUI objects and acts as the bridge between MixerUI and ControlsUI and MelodyUI
 @see MelodyUI, MelodySequencer
 */

#include <stdio.h>
#include "../../JuceLibraryCode/JuceHeader.h"
#include "../audio/Audio.h"
#include "../MelodySequencer/MelodyUI.hpp"


class MelodySequencerUI :   public Component,
                            public Button::Listener
{
public:
    /** constructor, needs a reference to the audio object */
    MelodySequencerUI(Audio& a);
    
    /** destructor */
    ~MelodySequencerUI();
    
    /** starts the audio */
    void play();
    
    /** checks if one of the sequencers are solo */
    void checkForSolos();
    
    /** checks if another component is mute */
    void checkForMutes();
    
    /** changes the gain of all the sequencers */
    void changeGain(float newGain);
    
    /** updates the state of the sequencer */
    void timerCalled();
    
    /** sets the file to be loaded */
    void setFile(File* file);
    
    /** retrieves the information and loads a scene */
    void loadScene(int numOfSequencer, int numOfStep, bool shouldBeActive) { melodySeq[numOfSequencer]->loadScene(numOfStep, shouldBeActive); }
    
    /** returns true if the current step is active */
    bool isStepActive(int numOfSequencer, int numOfStep) { return melodySeq[numOfSequencer]->shouldPlay(numOfStep); }
    
    void buttonClicked(Button* button) override;
    
    void resized() override;
    
    void paint(Graphics &g) override;
    
private:
    Audio& audio;
    static const int numOfSequencers = 8;
    
    MelodyUI* melodySeq[numOfSequencers];
    
    int sequencerPos;
    int time;
    
    TimeSliceThread thread;
    
    TextButton clearAllButton;
};


#endif /* MelodySequencerUI_hpp */
