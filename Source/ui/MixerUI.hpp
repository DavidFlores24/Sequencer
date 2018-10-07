//
//  MixerUI.hpp
//  JuceBasicAudio
//
//  Created by David Flores on 25/11/2016.
//
//

#ifndef MixerUI_hpp
#define MixerUI_hpp

/**
 Class that includes a mixer which allows to change gain and sync tempo. Communicates with MelodySequencerUI and DrumSequencerUI.
 @see MelodySequencerUI, DrumSequencerUI
 */

#include <stdio.h>
#include "../../JuceLibraryCode/JuceHeader.h"
#include "../DrumSequencer/DrumSequencerUI.hpp"
#include "../MelodySequencer/MelodySequencerUI.hpp"

class MixerUI   :   public Component,
                    public Slider::Listener,
                    public Button::Listener,
                    public Timer,
                    public ChangeBroadcaster
{
public:
    /** constructor, needs a reference to the melody sequencer and to the drum sequencer */
    MixerUI(MelodySequencerUI& ms, DrumSequencerUI& ds);
    
    /** destructor */
    ~MixerUI();
    
    /** changes the gain with the sliders of the individual components */
    void changeGain(int index, float newGain);
    
    /** starts the sequencer */
    void play();
    
    /** pauses the sequencer */
    void pause() {stopTimer();}
    
    /** called when the selectFileButton is pressed, opens up a dialogue box for the user to select the folder where the samples are */
    void chooseFiles();
        
    void resized() override;
    
    void paint(Graphics& g) override;
    
    void buttonClicked(Button* button) override;
    
    void sliderValueChanged(Slider* slider) override;
    
    void timerCallback() override;
    
private:
    Slider drumSlider;
    Slider melodySlider;
    
    Slider tempoSlider;
    
    TextButton syncButton;
    TextButton selectFileButton;
    
    Label drumLabel;
    Label melodyLabel;
    
    DrumSequencerUI& drumSequencer;
    MelodySequencerUI& melodySequencer;
};

#endif /* MixerUI_hpp */
