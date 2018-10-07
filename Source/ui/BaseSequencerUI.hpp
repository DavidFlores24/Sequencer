//
//  BaseSequencerUI.hpp
//  JuceBasicAudio
//
//  Created by David Flores on 28/11/2016.
//
//

#ifndef BaseSequencerUI_hpp
#define BaseSequencerUI_hpp

#include <stdio.h>
#include "../../JuceLibraryCode/JuceHeader.h"

/**
 Base class for the UI element of the rows in the sequencer, takes care of most UI functions and loads different scenes when required
 */

class BaseSequencerUI   :   public Component,
                            public Button::Listener

{
public:
    /** constructor */
    BaseSequencerUI();
    
    /** destructor */
    virtual ~BaseSequencerUI();
    
    /** returns true if the row is solo */
    bool isSolo()   { return soloState; }
    
    /** clears all the active buttons */
    void clearAll();
    
    /** assigns an ID to the sequencer so it knows what file to load 
        override in order to assign your own files and IDs */
    virtual void assignID(int newID) = 0;
    
    /** returns true if something else is solo override to fit the number
        of sequencers */
    virtual void somethingElseIsSolo(bool anotherSequencerIsSolo) = 0;
    
    /** mutes the row, override to fit the number
     of sequencers */
    virtual void mute() = 0;
    
    /** unmutes the row, override to fit the number
     of sequencers */
    virtual void unmute() = 0;
    
    /** changes the gain of the sequencer, override to fit the number
     of sequencers */
    virtual void changeGain(float newGain) = 0;
    
    /** returns true if step is active at the sequencer pos */
    bool shouldPlay(int sequencerPos);
    
    /** returns true if its been muted */
    bool shouldMute();
    
    /** loads a scene with the information passed */
    void loadScene(int numOfStep, bool shouldBeActive)
    {
        shouldBeActive ? step[numOfStep].setToggleState(true, dontSendNotification) :
        step[numOfStep].setToggleState(false, dontSendNotification);
    }
    
    void resized() override;
    
    void buttonClicked(Button* button) override;
    
    void paint(Graphics& g) override;
    
private:
    static const int numOfSteps = 8;
    TextButton step[numOfSteps];
    
    bool soloState;
    bool muteState;
    
    TextButton muteButton;
    TextButton soloButton;
};

#endif /* BaseSequencerUI_hpp */
