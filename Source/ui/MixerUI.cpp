//
//  MixerUI.cpp
//  JuceBasicAudio
//
//  Created by David Flores on 25/11/2016.
//
//

#include "MixerUI.hpp"

enum sequencers
{
    drum = 0,
    melody
};

MixerUI::MixerUI(MelodySequencerUI& ms, DrumSequencerUI& ds)  : drumSequencer(ds),
                                                                melodySequencer(ms)

{
    drumSlider.setSliderStyle(Slider::SliderStyle::LinearBarVertical);
    drumSlider.setRange(0.0, 1.0, 0.1);
    drumSlider.setValue(0.5);
    drumSlider.setColour(Slider::ColourIds::backgroundColourId, Colours::darkred);
    drumSlider.setColour(Slider::ColourIds::thumbColourId, Colours::darkorange);
    drumSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxBelow, false, 40, 15);
    addAndMakeVisible(drumSlider);
    drumSlider.addListener(this);
    
    drumLabel.setFont(13);
    drumLabel.setColour(Label::ColourIds::textColourId, Colours::cornsilk);
    drumLabel.setText("Drum Sequencer", dontSendNotification);
    addAndMakeVisible(drumLabel);
    
    melodySlider.setSliderStyle(Slider::SliderStyle::LinearBarVertical);
    melodySlider.setRange(0.0, 1.0, 0.1);
    melodySlider.setValue(0.5);
    melodySlider.setColour(Slider::ColourIds::backgroundColourId, Colours::darkred);
    melodySlider.setColour(Slider::ColourIds::thumbColourId, Colours::darkorange);
    melodySlider.setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxBelow, false, 40, 15);
    addAndMakeVisible(melodySlider);
    melodySlider.addListener(this);
    
    melodyLabel.setFont(13);
    melodyLabel.setColour(Label::ColourIds::textColourId, Colours::cornsilk);
    melodyLabel.setText("Melody Sequencer", dontSendNotification);
    addAndMakeVisible(melodyLabel);
    
    tempoSlider.setRange(100, 500, 1.0);
    tempoSlider.setSliderStyle(Slider::SliderStyle::Rotary);
    addAndMakeVisible(tempoSlider);
    tempoSlider.setColour(Slider::textBoxBackgroundColourId, Colours::grey);
    tempoSlider.setColour(Slider::rotarySliderFillColourId, Colours::darkred);
    tempoSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 40, 15);
    tempoSlider.addListener(this);
    
    syncButton.setButtonText("Sync Tempo");
    syncButton.setColour(TextButton::buttonColourId, Colours::darkgrey);
    syncButton.setColour(TextButton::textColourOffId, Colours::black);
    syncButton.addListener(this);
    addAndMakeVisible(syncButton);
    
    selectFileButton.setButtonText("Select Samples");
    selectFileButton.setColour(TextButton::buttonColourId, Colours::darkgrey);
    selectFileButton.setColour(TextButton::buttonOnColourId, Colours::black);
    selectFileButton.addListener(this);
    addAndMakeVisible(selectFileButton);
    
}

MixerUI::~MixerUI()
{
    
}

void MixerUI::resized()
{
    drumSlider.setBounds(20, 27, 30, getHeight() - 30);
    melodySlider.setBounds(drumSlider.getX()+ 100, drumSlider.getY(), drumSlider.getWidth(), drumSlider.getHeight());
    
    drumLabel.setBounds(drumSlider.getX()-12, 0, drumSlider.getWidth()+70, drumSlider.getWidth()+10);
    melodyLabel.setBounds(melodySlider.getX()-12, 0, melodySlider.getWidth()+70, melodySlider.getWidth()+10);
    
    tempoSlider.setBounds(melodySlider.getX()+100, 10, 60, 60);
    syncButton.setBounds(tempoSlider.getX(), tempoSlider.getY()+ 70, 60, 50);
    syncButton.setEnabled(false);
    
    selectFileButton.setBounds(tempoSlider.getX() + 90, syncButton.getY() + 5, getWidth()/4, 40);
}

void MixerUI::paint(Graphics& g)
{
    g.setColour(Colours::darkgrey);
    g.setOpacity(0.4);
    g.fillAll();
}

void MixerUI::buttonClicked(Button* button)
{
    if (&syncButton == button)
    {
        sendChangeMessage();    // let the listeners know that the usr has requested a tempo change
        syncButton.setEnabled(false);
    }
    
    else if(&selectFileButton == button)
    {
        chooseFiles();
    }
}

void MixerUI::sliderValueChanged(Slider* slider)
{
    if(&drumSlider == slider)
    {
        changeGain(drum, drumSlider.getValue());    // set the gain for the drumSequencer
    }
    
    else if(&melodySlider == slider)
    {
        changeGain(melody, melodySlider.getValue());    // set the gain for the melodySequencer
    }
    
    else if(&tempoSlider == slider)
    {
        syncButton.setEnabled(true);    // the syncButton is only enabled if the user has changed the tempo
    }
}

void MixerUI::changeGain(int index, float newGain)
{
    if (index == melody)
        melodySequencer.changeGain(newGain);
    
    else if(index == drum)
        drumSequencer.changeGain(newGain);
    
}

void MixerUI::timerCallback()
{
    melodySequencer.timerCalled();  // let the sequencers know that the timer has been updated
    drumSequencer.timerCalled();
}

void MixerUI::play()
{
    startTimer(60000/tempoSlider.getValue());   // convert the BPM into ms and start the timer to that value
}

void MixerUI::chooseFiles()
{
    FileChooser chooser("Please select a folder with your samples", File::getSpecialLocation(File::userMusicDirectory));
    
    if(chooser.browseForDirectory() == true)
    {
        File file(chooser.getResult());
        if(file.getFileName() == "Sounds")
        {
            drumSequencer.setFile(&file);   // send the directory to the drumSequencer
            melodySequencer.setFile(&file); // send the directory to the melodySequencer
            selectFileButton.setEnabled(false); // the usr is only allowed to select the samples once
        }
        else
        {
            // if the user selected a folder not named Sounds then alert him
            AlertWindow::showMessageBox(AlertWindow::WarningIcon, "Error!", "The directory selected is invalid");
        }
    }
}

