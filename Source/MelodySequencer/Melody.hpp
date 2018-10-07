//
//  Melody.hpp
//  JuceBasicAudio
//
//  Created by David Flores on 24/11/2016.
//
//

#ifndef Melody_hpp
#define Melody_hpp

/**
 MelodySequencer class, loads samples into the steps generated in the melody UI.
 
 @see BaseSequencer, MelodyUI, MelodySequencerUI
 
 */

#include <stdio.h>
#include "../BaseSequencer/BaseSequencer.hpp"

class MelodySequencer   :   public BaseSequencer
{
public:
    /** Constructor */
    MelodySequencer();
    
    /** destructor */
    ~MelodySequencer();
    
    // baseSequencer functions
    void assignID(int newSequencerID) override  { sequencerID = newSequencerID; }
    
    void setFile(File* file) override;
        
private:
    int sequencerID;
};

#endif /* Melody_hpp */
