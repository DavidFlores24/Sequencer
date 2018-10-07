//
//  ControlsUI.cpp
//  JuceBasicAudio
//
//  Created by David Flores on 25/11/2016.
//
//

#include "ControlsUI.hpp"

ControlsUI::ControlsUI(MelodySequencerUI& ms, DrumSequencerUI& ds, MixerUI& mui) :  melodySequencer(ms),
                                                                                    drumSequencer(ds),
                                                                                    mixerUI(mui)
{
    playButton.setButtonText(">");
    playButton.setColour(TextButton::ColourIds::buttonColourId, Colours::grey);
    playButton.addListener(this);
    playButton.setToggleState(false, dontSendNotification);
    addAndMakeVisible(playButton);
    
    pauseButton.setButtonText("||");
    pauseButton.setColour(TextButton::ColourIds::buttonColourId, Colours::grey);
    pauseButton.addListener(this);
    pauseButton.setToggleState(false, dontSendNotification);
    pauseButton.setEnabled(false);
    addAndMakeVisible(pauseButton);
    
    recordButton.setButtonText("R");
    recordButton.setColour(TextButton::buttonColourId, Colours::darkred);
    recordButton.setColour(TextButton::buttonOnColourId, Colours::red);
    recordButton.addListener(this);
    recordButton.setToggleState(false, dontSendNotification);
    addAndMakeVisible(recordButton);
    
    nameLabel.setText("Orbit", dontSendNotification);
    nameLabel.setFont(Font("avenir", 30, 0));
    nameLabel.setColour(Label::ColourIds::textColourId, Colours::grey);
    addAndMakeVisible(nameLabel);
    
    davidLabel.setText("by David Flores", dontSendNotification);
    davidLabel.setFont(Font("Copperplate", 10, 0));
    davidLabel.setColour(Label::ColourIds::textColourId, Colours::grey);
    addAndMakeVisible(davidLabel);
    
    sceneButton[0].setButtonText("1");
    sceneButton[1].setButtonText("2");
    sceneButton[2].setButtonText("3");
    sceneButton[3].setButtonText("4");
    
    timerLoops = 0;
    
    mixerUI.addChangeListener(this);    // if the user wants to update the tempo then we need to listen to the mixerUI
    
    for (int i = 0; i<4; i++)
    {
        sceneButton[i].addListener(this);
        addAndMakeVisible(sceneButton[i]);
        sceneButton[i].setColour(TextButton::ColourIds::buttonColourId, Colours::grey);
    }
    
    activeScene = 1;
    sceneToLoad = 0;
    
    /*  @param drumSequencerScene @param melodySequencerScene are 3D array that store bool values for the steps in the sequencers, the first value (i) is the number of scene, the second (i1) is the number of sequencer rows each contain and the third (i3) is the number of columns
     */
    
    for (int i = 0; i<4; i++)                       // these two for loops make sure that our scenes are clean
    {
        for (int i1 = 0; i1<4; i1++)
        {
            for (int i2 = 0; i2 <8; i2++)
                drumSequencerScene[i][i1][i2] = 0;
        }
    }
    
    for (int i = 0; i<4; i++)
    {
        for (int i1 = 0; i1<8; i1++)
        {
            for (int i2 = 0; i2 <8; i2++)
                melodySequencerScene[i][i1][i2] = 0;
        }
    }
}

ControlsUI::~ControlsUI()
{
    stopTimer();
}

void ControlsUI::changeScene()
{
    /* @param thereIsData this int remains 0 unless one or more of the steps in either sequencer are active. If thereIsData is greater than 0 then the scene is considered to store one or more steps activated by the users. This information is displayed in the GUI with the colours underneath the scenes buttons
     */
    int thereIsData = 0;
    for(int numOfSequencer = 0; numOfSequencer<4; numOfSequencer++)
    {
        for(int numOfStep = 0; numOfStep < 8; numOfStep++)
        {
            drumSequencerScene[activeScene][numOfSequencer][numOfStep] = drumSequencer.isStepActive(numOfSequencer, numOfStep);
            if (drumSequencer.isStepActive(numOfSequencer, numOfStep))
                thereIsData++;
        }
    }
    
    for (int numOfSequencer = 0; numOfSequencer<8; numOfSequencer++)
    {
        for (int numOfStep = 0; numOfStep < 8; numOfStep++)
        {
            melodySequencerScene[activeScene][numOfSequencer][numOfStep] = melodySequencer.isStepActive(numOfSequencer, numOfStep);
            if(melodySequencer.isStepActive(numOfSequencer, numOfStep))
                thereIsData++;
        }
    }
    
    // checks the condition to display the current state of the activeScene
    thereIsData == 0 ? savedData[activeScene] = false : savedData[activeScene] = true;
    
    // these two loops retrieve the information of the scene the user has requested to load
    for (int numOfSequencer = 0; numOfSequencer<4; numOfSequencer++)
    {
        for(int numOfStep = 0; numOfStep < 8; numOfStep++)
            drumSequencer.loadScene(numOfSequencer, numOfStep, drumSequencerScene[sceneToLoad][numOfSequencer][numOfStep]);
    }
    
    for (int numOfSequencer = 0; numOfSequencer<8; numOfSequencer++)
    {
        for(int numOfStep = 0; numOfStep < 8; numOfStep++)
            melodySequencer.loadScene(numOfSequencer, numOfStep, melodySequencerScene[sceneToLoad][numOfSequencer][numOfStep]);
    }

}


void ControlsUI::buttonClicked(Button* button)
{
    
    if(!button->getToggleState())
        button->setToggleState(true, dontSendNotification);
    else
        button->setToggleState(false, dontSendNotification);

    
    if(&playButton == button)
    {
        mixerUI.play();
        pauseButton.setEnabled(true);
        pauseButton.setToggleState(false, dontSendNotification);
    }
    
    else if(&pauseButton == button)
    {
        mixerUI.pause();
        playButton.setEnabled(true);
        playButton.setToggleState(false, dontSendNotification);
    }
    
    else if(&recordButton == button)
    {
        sendChangeMessage();    // let the MainComponent know that the usr has requested to record
        startTimer(500);        // this timer controls the flashing of the record button
        isRed = false;
    }
    
    else                        // if none of the above buttons were pressed then its safe to assume that it was a scene button
    {
        for (int i = 0; i<4; i++)   // check which one was pressed
        {
            if (&sceneButton[i] == button)
            {
                sceneToLoad = i+1;  // start the save and loading scene
                changeScene();
                repaint();
                activeScene = i+1;  // update the active scene
            }
            else
                sceneButton[i].setToggleState(false, dontSendNotification);
        }
    }
}

void ControlsUI::resized()
{
    playButton.setBounds(10, getHeight()/3+10, 40, 40);
    pauseButton.setBounds(playButton.getX()+70, playButton.getY(), playButton.getWidth(), playButton.getHeight());
    recordButton.setBounds(pauseButton.getX()+70, playButton.getY(), playButton.getWidth(), playButton.getHeight());
    nameLabel.setBounds(getWidth()/2+50, getHeight()/3, getWidth()/2, 50);
    davidLabel.setBounds(nameLabel.getX(), nameLabel.getY()+20, nameLabel.getWidth()-10, nameLabel.getHeight());
    
    for (int i = 0; i<4; i++)
        sceneButton[i].setBounds(playButton.getX() + (i * 30), playButton.getY()+60, playButton.getWidth()-20, playButton.getHeight()-20);
}

void ControlsUI::paint(Graphics& g)
{
    g.setColour(Colours::darkgrey);
    g.setOpacity(0.4);
    g.fillAll();
    
    for (int i = 0; i<4; i++)   // check which scene the usr is working on and paint accordingly
    {
        i+1 == activeScene ? g.setColour(Colours::darkgoldenrod) : g.setColour(Colours::forestgreen);
        
        if(sceneHasData(i+1) && activeScene != i+1) // if the scene has data then alert the usr
            g.setColour(Colours::darkred);
        
        g.fillRect(10 + i * 30, getHeight()/3 + 90, 20, 7);
    }
    
    if(recordButton.getToggleState())
    {
        isRed ? g.setColour(Colours::ivory) : g.setColour(Colours::darkred);
        isRed ? isRed = false : isRed = true;
        
        g.setOpacity(0.5);
        
        g.fillRect(recordButton.getX()-2, recordButton.getY()-2, recordButton.getHeight()+4, recordButton.getWidth()+4);
    }
}

void ControlsUI::timerCallback()
{
    if(recordButton.getToggleState())
        repaint();
    
    timerLoops++;
    
    if(timerLoops == 60)
    {
        stopTimer();
        recordButton.setToggleState(false, dontSendNotification);
        isRed = false;  // @param isRed is a bool that checks what light the record button is currently on
        timerLoops = 0;
        sendChangeMessage();    // let MainComponent know that the record button has been released
    }
}

void ControlsUI::changeToggleStates(bool pauseButtonShouldBePressed, bool playButtonShouldBePressed)
{
    pauseButton.setToggleState(pauseButtonShouldBePressed, dontSendNotification);
    playButton.setToggleState(playButtonShouldBePressed, dontSendNotification);
}

void ControlsUI::changeListenerCallback(ChangeBroadcaster* source)
{
    if(&mixerUI == source)
    {
        if(playButtonIsPressed())
        {
            mixerUI.pause();
            mixerUI.play();
        }
    }
}
