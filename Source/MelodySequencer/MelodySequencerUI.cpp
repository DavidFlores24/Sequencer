//
//  MelodySequencerUI.cpp
//  JuceBasicAudio
//
//  Created by David Flores on 24/11/2016.
//
//

#include "MelodySequencerUI.hpp"

enum note
{
    e = 0,
    fSharp,
    g,
    a,
    b,
    c,
    d,
    e2
};

MelodySequencerUI::MelodySequencerUI(Audio& a)  :   audio(a),
                                                    thread("melodySequencerThread")
{
    for (int i = 0; i<numOfSequencers; i++)
    {
        melodySeq[i] = new MelodyUI(a.getMelodySeq(i));
        melodySeq[i]->assignID(i);
        addAndMakeVisible(melodySeq[i]);
    }
    
    clearAllButton.setButtonText("Clear All");
    clearAllButton.setColour(TextButton::buttonColourId, Colours::darkgrey);
    clearAllButton.setColour(TextButton::textColourOffId, Colours::black);
    clearAllButton.addListener(this);
    addAndMakeVisible(clearAllButton);
    
    for (int i = 0; i<numOfSequencers; i++)
        melodySeq[i]->clearAll();
    
    time = 0;
    sequencerPos = 0;
}

MelodySequencerUI::~MelodySequencerUI()
{
    for (int i= 0; i<numOfSequencers; i++)
    {
        delete melodySeq[i];
    }
    thread.stopThread(100);
}

void MelodySequencerUI::resized()
{
    int y = 10;
    
    for (int i = 0; i<numOfSequencers; i++)
    {
        melodySeq[i]->setBounds(10, y, getWidth()-53, getWidth()/10);
        y+=41;
    }
    

    clearAllButton.setBounds(melodySeq[0]->getX() + 400, 110, getWidth()/6, 30);
}

void MelodySequencerUI::paint(Graphics& g)
{
    g.setColour(Colours::darkgrey);
    g.setOpacity(0.6);
    g.fillAll();
    
    int x = melodySeq[0]->getWidth() / 8 - 10;
    g.setColour(Colours::ivory);
    g.fillRect(x*sequencerPos + 11, 10, x, (melodySeq[0]->getHeight()*7) - 24);
}

void MelodySequencerUI::timerCalled()
{
    sequencerPos++;
    sequencerPos > 7 ? sequencerPos = 0 : NULL;
    repaint();
    checkForSolos();
    checkForMutes();
    play();
}

void MelodySequencerUI::play()
{    
    for (int i = 0; i<numOfSequencers; i++)
        melodySeq[i]->play(sequencerPos);
}

void MelodySequencerUI::checkForSolos()
{
    bool somethingIsSolo = false;
    
    for (int i = 0; i<numOfSequencers; i++)
    {
        if(melodySeq[i]->isSolo())
        {
            somethingIsSolo = true;
            
            for (int in = 0; in < numOfSequencers; in++)
            {
                if (in != i)
                {
                    melodySeq[in] ->somethingElseIsSolo(true);
                }
                
            }
        }
        
        if(!somethingIsSolo)
        {
            melodySeq[i]->somethingElseIsSolo(false);
        }
    }
}

void MelodySequencerUI::buttonClicked(Button* button)
{
    if (&clearAllButton == button)
    {
        for (int i = 0; i<numOfSequencers; i++)
            melodySeq[i]->clearAll();
    }
}

void MelodySequencerUI::changeGain(float newGain)
{
    for (int i = 0; i<numOfSequencers; i++)
    {
        melodySeq[i]->changeGain(newGain);
    }
}

void MelodySequencerUI::checkForMutes()
{
    for(int i = 0; i<4; i++)
        if(melodySeq[i]->shouldMute())
            melodySeq[i]->mute();
        else
            melodySeq[i]->unmute();
}

void MelodySequencerUI::setFile(File* file)
{
    for(int i = 0; i<numOfSequencers; i++)
        melodySeq[i]->setFile(file);
}
