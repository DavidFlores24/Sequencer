//
//  BaseSequencerUI.cpp
//  JuceBasicAudio
//
//  Created by David Flores on 28/11/2016.
//
//

#include "BaseSequencerUI.hpp"

BaseSequencerUI::BaseSequencerUI()
{
    for (int i = 0; i<numOfSteps; i++)
    {
        step[i].setColour(TextButton::ColourIds::buttonOnColourId, Colours::darkred);
        step[i].setColour(TextButton::ColourIds::buttonColourId, Colours::darkorange);
        step[i].addListener(this);
        step[i].setToggleState(false, dontSendNotification);
        addAndMakeVisible(step[i]);
    }
    
    muteButton.setButtonText("m");
    muteButton.addListener(this);
    addAndMakeVisible(muteButton);
    
    soloButton.setButtonText("s");
    soloButton.addListener(this);
    addAndMakeVisible(soloButton);
    
    muteState = false;
    soloState = false;
}

BaseSequencerUI::~BaseSequencerUI()
{
    
}

void BaseSequencerUI::resized()
{
    int x = 1;
    int width = getWidth()/8 - 10;
    int height = getHeight() - 10;
    for (int i = 0; i<8; i++)
    {
        step[i].setBounds(x, 1, width, height);
        x+=45;
    }
    muteButton.setBounds(step[7].getX() + getWidth()/8-8, step[7].getY(), 15, 15);
    soloButton.setBounds(step[7].getX() + getWidth()/8-8, muteButton.getY() +15, 15, 15);
}

void BaseSequencerUI::paint(Graphics& g)
{
    g.setOpacity(0.0);
    
    // make a GUI change to let the usr know if one row is muted or solo
    if(muteState)
    {
        g.setColour(Colours::darkblue);
        g.setOpacity(1.0);
    }
    
    if(soloState == true)
    {
        g.setColour(Colours::darkgoldenrod);
        g.setOpacity(1.0);
    }
    
    if(!muteState && !soloState)
        g.setOpacity(0.0);
    
    g.fillRect(step[0].getX(), step[0].getY(), step[0].getWidth() * 8, step[0].getHeight());
}


void BaseSequencerUI::buttonClicked(Button* button)
{
    if(!button->getToggleState())
        button->setToggleState(true, dontSendNotification);
    else
        button->setToggleState(false, dontSendNotification);
    
    if(&muteButton == button)
    {
        button->getToggleStateValue() == true ? muteState = true : muteState = false;
        repaint();
    }
    
    else if (&soloButton == button)
    {
        button->getToggleStateValue() == true ? soloState = true : soloState = false;
        repaint();
    }
}

void BaseSequencerUI::clearAll()
{
    for (int i = 0; i<8; i++)
    {
        step[i].setToggleState(false, dontSendNotification);    // make all the steps inactive
    }
}

bool BaseSequencerUI::shouldPlay(int sequencerPos)
{
    return step[sequencerPos].getToggleState(); // returns true if the step at the sequencer position has been pressed
}

bool BaseSequencerUI::shouldMute()
{
    return muteState;
}
