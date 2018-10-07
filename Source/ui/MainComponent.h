/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#ifndef MAINCOMPONENT_H_INCLUDED
#define MAINCOMPONENT_H_INCLUDED

#include "../../JuceLibraryCode/JuceHeader.h"
#include "../audio/Audio.h"
#include "../DrumSequencer/SequencerUI.hpp"
#include "../DrumSequencer/DrumSequencerUI.hpp"
#include "../MelodySequencer/MelodySequencerUI.hpp"
#include "../ui/MixerUI.hpp"
#include "../ui/ControlsUI.hpp"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
 @param drumSequencer Instance of the DrumSequencerUI class, @see DrumSequencerUI
 @param melodySequencer Instance of the MelodySequencerUI class, @see MelodySequencerUI
*/
class MainComponent   : public Component,
                        public ChangeListener
{
public:
    //==============================================================================
    /** Constructor */
    MainComponent (Audio& a);

    /** Destructor */
    ~MainComponent();
    
    void changeListenerCallback (ChangeBroadcaster* source) override;

    void resized() override;
    
    void paint(Graphics& g) override;
    
    /** takes an AudioSampleBuffer pointer, prompts the user to create a file that is stored into the desktop 
     @see audio::getBufferToSave(), MixerUI::recordButtonIsPressed()*/
    void record (AudioSampleBuffer* bufferToSave);
        
private:
    Audio& audio;
    DrumSequencerUI drumSequencer;
    MelodySequencerUI melodySequencer;
    MixerUI mixerUI;
    ControlsUI controlsUI;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};


#endif  // MAINCOMPONENT_H_INCLUDED
