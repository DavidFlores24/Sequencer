//
//  MelodyUI.hpp
//  JuceBasicAudio
//
//  Created by David Flores on 24/11/2016.
//
//

#ifndef MelodyUI_hpp
#define MelodyUI_hpp

/**
 MelodyUI class, generates one row of 8 steps and communicates with MelodySequencerUI and MelodySequencer.
 @see MelodySequencer, MelodySequencerUI
 */

#include <stdio.h>
#include "../../JuceLibraryCode/JuceHeader.h"
#include "../MelodySequencer/Melody.hpp"
#include "../ui/BaseSequencerUI.hpp"


class MelodyUI  :   public BaseSequencerUI
{
public:
    /** constructor, needs a reference to the sequencer */
    MelodyUI(MelodySequencer& melodySeq_);
    
    /** destructor */
    ~MelodyUI();

    /** assigns an ID to the sequencer so it knows what file to load */
    void assignID(int newID) override {melodySeq.assignID(newID); }
    
    /** asks if another component is solo */
    void somethingElseIsSolo(bool anotherSequencerIsSolo) override;

    /** mutes the row */
    void mute() override;
    
    /** unmutes the row */
    void unmute() override;
    
    /** changes the Gain of the sequencer */
    void changeGain(float newGain) override { melodySeq.changeGain(newGain); }
    
    /** sends the file directory to the melody sequencer @see BaseSequencer::setFile() */
    void setFile(File* file) { melodySeq.setFile(file); }
    
    void play(int sequencerPos);
    
private:
    MelodySequencer& melodySeq;

};
#endif /* MelodyUI_hpp */
