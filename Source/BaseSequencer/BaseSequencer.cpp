//
//  BaseSequencer.cpp
//  JuceBasicAudio
//
//  Created by David Flores on 24/11/2016.
//
//

#include "BaseSequencer.hpp"

BaseSequencer::BaseSequencer()
{
    
    muteState = false;
    muteBecauseOfSolo = false;
    gain = 0.5;
}

BaseSequencer::~BaseSequencer()
{
    audioTransportSource.stop();
    audioTransportSource.setSource (nullptr);
    delete currentAudioFileSource;
}

void BaseSequencer::setPlaying(bool newState)
{
    audioTransportSource.setPosition(0.0);
    audioTransportSource.start();
}

bool BaseSequencer::isPlaying() const
{
    return audioTransportSource.isPlaying();
}

void BaseSequencer::loadFile(const File& newFile)
{
    // load the corresponding file for this row of the sequencer
    AudioFormatManager formatManager;
    formatManager.registerBasicFormats();
    
    AudioFormatReader* reader = formatManager.createReaderFor(newFile);
    
    if (reader != 0)
    {
        currentAudioFileSource = new AudioFormatReaderSource(reader, true);
        audioTransportSource.setSource (currentAudioFileSource);
    }
}

void BaseSequencer::mute()
{
    audioTransportSource.setGain(0);
    muteState = true;
}

void BaseSequencer::unmute()
{
    if (!muteBecauseOfSolo)
        audioTransportSource.setGain(gain);
    
    muteState = false;
}

void BaseSequencer::mutedBecauseOfSolo()
{
    muteBecauseOfSolo = true;
    audioTransportSource.setGain(0);
}

void BaseSequencer::unmuteSolo()
{
    muteBecauseOfSolo = false;
    audioTransportSource.setGain(gain);
}

/* Audio Source Functions */

void BaseSequencer::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    audioTransportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void BaseSequencer::releaseResources()
{
    audioTransportSource.releaseResources();
}

void BaseSequencer::getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill)
{
    audioTransportSource.getNextAudioBlock(bufferToFill);
}
