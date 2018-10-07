//
//  DrumSequencerUI.hpp
//  JuceBasicAudio
//
//  Created by David Flores on 22/11/2016.
//
//

#ifndef DrumSequencerUI_hpp
#define DrumSequencerUI_hpp

/**
 DrumSequencerUI contains 4 sequencerUI objects and acts as a bridge between MixerUI and ControlsUI and SequencerUI.
 @see MixerUI, ControlsUI, SequencerUI
 */

#include <stdio.h>
#include "../../JuceLibraryCode/JuceHeader.h"
#include "../DrumSequencer/SequencerUI.hpp"
#include "../audio/Audio.h"

class DrumSequencerUI : public Component,
                        public Button::Listener
{
public:
    /** constructor, needs a reference to the audio object */
    DrumSequencerUI(Audio& a);
    
    /** destructor */
    ~DrumSequencerUI();
    
    /** starts the audio */
    void play();
    
    /** checks if one of the sequencers are solo */
    void checkForSolos();
    
    void checkForMutes();
    
    /** returns sequencerPos */
    int getSequencerPos() { return sequencerPos; }
    
    /** returns true if the current step is active */
    bool isStepActive(int numOfSequencer, int numOfStep);
    
    /** retrieves the information and loads a scene */
    void loadScene(int numOfSequencer, int numOfStep, bool shouldBeActive);
    
    /** updates the state of the sequencer */
    void timerCalled();
    
    /** sets the file to be loaded */
    void setFile(File* fileDirectory);
    
    void buttonClicked(Button* button) override;
    
    void changeGain(float newGain);
    
    void resized() override;
    
    void paint(Graphics &g) override;
    
private:
    Audio& audio;
    static const int numOfSequencers = 4;
    
    SequencerUI* sequencer[numOfSequencers];
    
    Slider tempoSlider;
    int sequencerPos;
    int time;
    
    TimeSliceThread thread;
    
    TextButton clearAllButton;
};

#endif /* DrumSequencerUI_hpp */
