//
//  Sequencer.hpp
//  JuceBasicAudio
//
//  Created by David Flores on 22/11/2016.
//
//

#ifndef Sequencer_hpp
#define Sequencer_hpp

/**
 Sequencer class for the drum sequencer, inherits from BaseSequencer and loads the sample for the drumSequencer.
 @see BaseSequencer, SequencerUI, DrumSequencerUI
 */

#include <stdio.h>
#include "../../JuceLibraryCode/JuceHeader.h"
#include "../BaseSequencer/BaseSequencer.hpp"

class Drum :   public BaseSequencer
{
public:
    /** constructor */
    Drum();
    
    /** destructor */
    ~Drum();
    
    void setFile(File* file) override;
    
    /** assigns an ID to the sequencer so it knows what file to load */
    void assignID(int newSequencerID) override  { sequencerID = newSequencerID; }
    
private:
    int sequencerID;
};

#endif /* Sequencer_hpp */
