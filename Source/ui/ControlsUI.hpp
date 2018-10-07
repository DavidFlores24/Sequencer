//
//  ControlsUI.hpp
//  JuceBasicAudio
//
//  Created by David Flores on 25/11/2016.
//
//

#ifndef ControlsUI_hpp
#define ControlsUI_hpp

/**
 Class that includes play and pause button as well as name of the application and save and load scenes feature. Communicates with MelodySequencerUI and DrumSequencerUI and MixerUI
 
 @see MelodySequencerUI, DrumSequencerUI, MixerUI
 */

#include <stdio.h>
#include "../../JuceLibraryCode/JuceHeader.h"
#include "../DrumSequencer/DrumSequencerUI.hpp"
#include "../MelodySequencer/MelodySequencerUI.hpp"
#include "../ui/MixerUI.hpp"

class ControlsUI    :   public Timer,
                        public Component,
                        public Button::Listener,
                        public ChangeBroadcaster,
                        public ChangeListener
{
public:
    /** construcor, needs a reference to melodySequencerUI and DrumSequencerUI */
    ControlsUI(MelodySequencerUI& ms, DrumSequencerUI& ds, MixerUI& mui);
    
    /** destructor */
    ~ControlsUI();
    
    /** saves current data and loads data for the respective scene */
    void changeScene();
    
    /** returns true if the scene has at least one button active */
    bool sceneHasData(int sceneNum) { return savedData[sceneNum]; }
    
    /** returns toggle state of the playButton */
    bool playButtonIsPressed() { return playButton.getToggleState(); }
    
    /** returns toggle state of the recordButton 
     @see MainComponent::record(), @audio::getBufferToSave()
     @param timerLoops int that stores the amount of times the record Button has flashed*/
    bool recordButtonIsPressed() { return recordButton.getToggleState(); }
    
    void changeListenerCallback(ChangeBroadcaster* source) override;
    
    /** changes the toggle states of the pause and play button*/
    void changeToggleStates(bool pauseButtonShouldBePressed, bool playButtonShouldBePressed);
    
    void resized() override;
    
    void paint(Graphics& g) override;
    
    void buttonClicked(Button* button) override;
    
    void timerCallback() override;
    
private:
    MelodySequencerUI& melodySequencer;
    DrumSequencerUI& drumSequencer;
    
    MixerUI& mixerUI;
    
    TextButton playButton;
    TextButton pauseButton;
    TextButton sceneButton[4];
    TextButton recordButton;
    
    Label nameLabel;
    Label davidLabel;
    
    int activeScene;
    int sceneToLoad;
    bool savedData[4];
    bool drumSequencerScene[4][4][8];
    bool melodySequencerScene[4][8][8];
    bool isRed;
    
    int timerLoops;
};

#endif /* ControlsUI_hpp */
