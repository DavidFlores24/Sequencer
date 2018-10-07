//
//  Sequencer.cpp
//  JuceBasicAudio
//
//  Created by David Flores on 22/11/2016.
//
//

#include "Sequencer.hpp"

enum instrument
{
    kick = 0,
    snare,
    hihat,
    clap,
    no_of_instruments
};

Drum::Drum()
{
}

Drum::~Drum()
{
    
}

void Drum::setFile(File* file)
{
    switch(sequencerID)
    {
        case kick:
            loadFile(file->getChildFile("Drumkit/Kick.wav"));
            break;
            
        case snare:
            loadFile(file->getChildFile("Drumkit/Snare.wav"));
            break;
            
        case hihat:
            loadFile(file->getChildFile("Drumkit/HiHat.wav"));
            break;
            
        case clap:
            loadFile(file->getChildFile("Drumkit/Clap.wav"));
            break;
            
        default:
            break;
    }
}

