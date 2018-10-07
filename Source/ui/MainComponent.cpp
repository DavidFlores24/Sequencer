/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"


enum instrument
{
    kick = 0,
    snare,
    hihat,
    clap,
};


//==============================================================================
MainComponent::MainComponent (Audio& a) :   audio (a),
                                            drumSequencer(a),
                                            melodySequencer(a),
                                            mixerUI(melodySequencer, drumSequencer),
                                            controlsUI(melodySequencer, drumSequencer, mixerUI)
{
    setSize (1000, 500);
    addAndMakeVisible(drumSequencer);
    addAndMakeVisible(melodySequencer);
    addAndMakeVisible(mixerUI);
    addAndMakeVisible(controlsUI);
    controlsUI.addChangeListener(this);
    audio.addChangeListener(this);
}

MainComponent::~MainComponent()
{

}

void MainComponent::resized()
{
    drumSequencer.setBounds(0, 150, getWidth()/2, getHeight()-150);
    melodySequencer.setBounds(getWidth()/2, 150, getWidth()/2, getHeight()-150);
    mixerUI.setBounds(getWidth()/2, 0, getWidth()/2, getHeight()-melodySequencer.getHeight());
    controlsUI.setBounds(0, 0, getWidth()/2, getHeight()-drumSequencer.getHeight());
}


void MainComponent::paint(Graphics& g)
{
    g.setColour(Colours::white);
    g.drawLine(getWidth()/2, 0, getWidth()/2, getHeight());
    g.drawLine(0, 150, getWidth(), 150);
}


void MainComponent::changeListenerCallback(ChangeBroadcaster* source)
{
    if(&controlsUI == source)
    {
        if(controlsUI.recordButtonIsPressed())
            audio.recordButtonPressed(true);    // through here we alert the audio that the user has requested to record
        
        else
            audio.recordButtonPressed(false);
    }
    
    else if(&audio == source)
    {
        record(&audio.getBufferToSave());       // once the buffer is filled in audio then we retrieve it here in order to be thread safe
    }
}

void MainComponent::record(AudioSampleBuffer* bufferToSave)
{
    mixerUI.pause();                            // we pause the current audio process
    controlsUI.changeToggleStates(true, false); // make an evident change in the GUI
    FileChooser chooser("please select a file", File::getSpecialLocation(File::userDesktopDirectory), "*.wav"); // ask user for a directory
    if(chooser.browseForFileToSave(true))   // create the new file with the buffer that we retrieved from audio
    {
        File file(chooser.getResult().withFileExtension(".wav"));
        OutputStream* outStream = file.createOutputStream();
        WavAudioFormat wavFormat;
        AudioFormatWriter* writer = wavFormat.createWriterFor(outStream, 44100, 2, 16, NULL, 0);
        writer->writeFromAudioSampleBuffer(*bufferToSave, 0, bufferToSave->getNumSamples());
        
        delete writer;
    }
    // let the user know that everything went ok
    AlertWindow::showMessageBox(AlertWindow::InfoIcon, "Info:", "Maximum size of 30 sec reached, your file has been saved", "OK", this);
}

