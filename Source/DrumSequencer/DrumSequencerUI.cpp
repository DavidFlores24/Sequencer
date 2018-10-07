//
//  DrumSequencerUI.cpp
//  JuceBasicAudio
//
//  Created by David Flores on 22/11/2016.
//
//

#include "DrumSequencerUI.hpp"

enum instrument
{
    kick = 0,
    snare,
    hihat,
    clap,
};

DrumSequencerUI::DrumSequencerUI(Audio& a)  :   audio(a),
                                                thread("drumSequencerThread")
{
    thread.startThread();
    
    for (int i = 0; i<4; i++)
    {
        sequencer[i] = new SequencerUI(a.getSequencer(i));
        sequencer[i]->assignID(i);
        sequencer[i]->clearAll();
        addAndMakeVisible(sequencer[i]);
    }
    
    clearAllButton.setButtonText("Clear All");
    clearAllButton.setColour(TextButton::buttonColourId, Colours::darkgrey);
    clearAllButton.setColour(TextButton::textColourOffId, Colours::black);
    clearAllButton.addListener(this);
    addAndMakeVisible(clearAllButton);
    
    time = 0;
    
    sequencerPos = 0;
}


DrumSequencerUI::~DrumSequencerUI()
{
    for (int i = 0; i<4; i++)
    {
        delete sequencer[i];
    }
    thread.stopThread(100);
}

void DrumSequencerUI::resized()
{
    int y = 100;
    
    for (int i = 0; i<4; i++)
    {
        sequencer[i]->setBounds(10, y, getWidth()-53, getWidth()/10);
        y+=41;
    }
    
    clearAllButton.setBounds(10, y+40, getWidth()/4, 30);
}

void DrumSequencerUI::paint(Graphics& g)
{
    g.setColour(Colours::darkgrey);
    g.setOpacity(0.6);
    g.fillAll();
    
    int x = sequencer[0]->getWidth() / 8 - 10;
    g.setColour(Colours::ivory);
    g.fillRect(x*sequencerPos + 11, 100, x, (sequencer[0]->getHeight()*4) - 35);
}

void DrumSequencerUI::timerCalled()
{
    sequencerPos++;
    sequencerPos > 7 ? sequencerPos = 0 : NULL;
    repaint();
    checkForSolos();
    checkForMutes();
    play();
}

void DrumSequencerUI::play()
{
    for (int i= 0; i<4; i++)
    {
        sequencer[i]->play(sequencerPos);
    }
}

void DrumSequencerUI::checkForSolos()
{
    bool somethingIsSolo = false;
    
    for (int i = 0; i<4; i++)           // for loop that checks if one of the sequencer rows is solo
    {
        if(sequencer[i]->isSolo())
        {
            somethingIsSolo = true;
            for (int in = 0; in < 4; in++)
            {
                if (in != i)
                {
                    sequencer[in] ->somethingElseIsSolo(true);  // if one is solo then it alerts the remaining rows with the
                                                                // somethingElseIsSolo() function
                }
            }            
        }
        
        if(!somethingIsSolo)
        {
            sequencer[i]->somethingElseIsSolo(false);           // if nothing is solo keep updating the sequencer rows
        }
    }
}

void DrumSequencerUI::checkForMutes()
{
    for(int i = 0; i<4; i++)                                    // if the mute button has been pressed, shouldMute() will return true
        if(sequencer[i]->shouldMute())
            sequencer[i]->mute();
    else
        sequencer[i]->unmute();
}

void DrumSequencerUI::buttonClicked(Button* button)
{
    if (&clearAllButton == button)
    {
        for (int i = 0; i<4; i++)
            sequencer[i]->clearAll();
    }
}

void DrumSequencerUI::changeGain(float newGain)
{
    for (int i = 0; i<4;i++)
        sequencer[i]->changeGain(newGain);
}

bool DrumSequencerUI::isStepActive(int numOfSequencer, int numOfStep)
{
    return sequencer[numOfSequencer]->shouldPlay(numOfStep);
}

void DrumSequencerUI::loadScene(int numOfSequencer, int numOfStep, bool shouldBeActive)
{
    sequencer[numOfSequencer]->loadScene(numOfStep, shouldBeActive);
}

void DrumSequencerUI::setFile(File* fileDirectory)
{
    for(int i = 0; i<numOfSequencers; i++)
        sequencer[i]->setFile(fileDirectory);
}
