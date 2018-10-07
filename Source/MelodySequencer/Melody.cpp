//
//  Melody.cpp
//  JuceBasicAudio
//
//  Created by David Flores on 24/11/2016.
//
//

#include "Melody.hpp"

enum note
{
    e = 0,
    fSharp,
    g,
    a,
    b,
    c,
    d,
    e2,
    no_of_notes
};

MelodySequencer::MelodySequencer()
{
    
}

MelodySequencer::~MelodySequencer()
{
    releaseResources();
}

//void MelodySequencer::assignFile()
//{
//    const char* path[no_of_notes] =
//    { // TDDF: Make this more elegant.
//        "/Users/david/Documents/UWE/Year3/SDA/AssignmentTake2/Sounds/Melody/e.wav",
//        "/Users/david/Documents/UWE/Year3/SDA/AssignmentTake2/Sounds/Melody/fSharp.wav",
//        "/Users/david/Documents/UWE/Year3/SDA/AssignmentTake2/Sounds/Melody/g.wav",
//        "/Users/david/Documents/UWE/Year3/SDA/AssignmentTake2/Sounds/Melody/a.wav",
//        "/Users/david/Documents/UWE/Year3/SDA/AssignmentTake2/Sounds/Melody/b.wav",
//        "/Users/david/Documents/UWE/Year3/SDA/AssignmentTake2/Sounds/Melody/c.wav",
//        "/Users/david/Documents/UWE/Year3/SDA/AssignmentTake2/Sounds/Melody/d.wav",
//        "/Users/david/Documents/UWE/Year3/SDA/AssignmentTake2/Sounds/Melody/e2.wav"
//    };
//    
//    File file(path[sequencerID]);
//    loadFile(file);
//
//}

void MelodySequencer::setFile(File* file)
{
    switch (sequencerID)
    {
        case e:
            loadFile(file->getChildFile("Melody/e.wav"));
            break;
            
        case fSharp:
            loadFile(file->getChildFile("Melody/fSharp.wav"));
            break;
            
        case g:
            loadFile(file->getChildFile("Melody/g.wav"));
            break;
            
        case a:
            loadFile(file->getChildFile("Melody/a.wav"));
            break;
            
        case b:
            loadFile(file->getChildFile("Melody/b.wav"));
            break;
            
        case c:
            loadFile(file->getChildFile("Melody/c.wav"));
            break;
            
        case d:
            loadFile(file->getChildFile("Melody/d.wav"));
            break;
            
        case e2:
            loadFile(file->getChildFile("Melody/e2.wav"));
            break;
            
        default:
            break;
    }
}
