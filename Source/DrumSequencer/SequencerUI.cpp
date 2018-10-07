//
//  SequencerUI.cpp
//  JuceBasicAudio
//
//  Created by David Flores on 22/11/2016.
//
//

#include "SequencerUI.hpp"

SequencerUI::SequencerUI(Drum& sequencer_) : sequencer(sequencer_)
{
    gain = 0.5;
    
}

SequencerUI::~SequencerUI()
{
}


void SequencerUI::somethingElseIsSolo(bool anotherSequencerIsSolo)
{
    if (anotherSequencerIsSolo)             // if somethingElseIsSolo(true) then its important to mute the sequencer using
        sequencer.mutedBecauseOfSolo();     // the mutedBecauseOfSolo() function !!
    
    else
        sequencer.unmuteSolo();             // if the sequencer was muted using mutedBecauseOfSolo() you must use unmuteSolo() to unmute it
}

void SequencerUI::play(int sequencerPos)
{
   if(shouldPlay(sequencerPos))             // if the step is pressed at the current sequencerPos, shouldPlay will return true
       sequencer.setPlaying(true);
}

void SequencerUI::mute()
{
    if (shouldMute())
        sequencer.mute();
}

