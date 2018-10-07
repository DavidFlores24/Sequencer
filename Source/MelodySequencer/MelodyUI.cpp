//
//  MelodyUI.cpp
//  JuceBasicAudio
//
//  Created by David Flores on 24/11/2016.
//
//

#include "MelodyUI.hpp"

MelodyUI::MelodyUI(MelodySequencer& melodySeq_) :   melodySeq(melodySeq_)
{
    
}

MelodyUI::~MelodyUI()
{
}


void MelodyUI::somethingElseIsSolo(bool anotherSequencerIsSolo)
{
    anotherSequencerIsSolo == true ? melodySeq.mutedBecauseOfSolo() : melodySeq.unmuteSolo(); 
}

void MelodyUI::play(int sequencerPos)
{
    if (shouldPlay(sequencerPos))
        melodySeq.setPlaying(true);
}

void MelodyUI::mute()
{
    melodySeq.mute();
}

void MelodyUI::unmute()
{
    melodySeq.unmute();
}
