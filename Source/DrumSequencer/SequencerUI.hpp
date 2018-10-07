//
//  SequencerUI.hpp
//  JuceBasicAudio
//
//  Created by David Flores on 22/11/2016.
//
//

#ifndef SequencerUI_hpp
#define SequencerUI_hpp

/**
 This class is the UI for a single row of the sequencer, it is composed of buttons and works together with Sequencer and SequencerUI to control the sequencer, by using the assign ID it tells the sequencer what file it should load
 
 @see Sequencer, DrumSequencerUI
 */


#include <stdio.h>
#include "../../JuceLibraryCode/JuceHeader.h"
#include "../DrumSequencer/Sequencer.hpp"
#include "../BaseSequencer/BaseSequencer.hpp"
#include "../ui/BaseSequencerUI.hpp"

class SequencerUI   :   public BaseSequencerUI
{
public:
    /** constructor, needs a reference to a sequencer */
    SequencerUI(Drum& sequencer_);
    
    /** destructor */
    ~SequencerUI();
    
    /** assigns an ID to the sequencer so it knows what file to load */
    void assignID(int newID) override { sequencer.assignID(newID); }
    
    /** returns true if another row is solo */
    void somethingElseIsSolo(bool anotherSequencerIsSolo) override;
    
    /** mutes the row */
    void mute() override;
    
    /** unmutes the row */
    void unmute() override  { sequencer.unmute(); }
    
    void changeGain(float newGain) override { gain = newGain; sequencer.changeGain(newGain); }
    
    /** starts producing sound */
    void play(int sequencerPos);
    
    /** sends the file directory to the melody sequencer @see BaseSequencer::setFile() */
    void setFile(File* file) { sequencer.setFile(file); }
        
private:
    Drum& sequencer;
    float gain;
};
#endif /* SequencerUI_hpp */
