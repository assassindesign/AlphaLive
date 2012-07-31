//
//  PadSettings.h
//  AlphaSoft
//
//  Created by Liam Meredith-Lacey on 15/09/2011.
//  Copyright 2011 nu desine.
//
//  This file is part of AlphaLive.
//
//  AlphaLive is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License, version 2, 
//  as published by the Free Software Foundation.
//  
//  AlphaLive is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.
//

#ifndef H_PADSETTINGS
#define H_PADSETTINGS

//==================================================================
/**
 This class is used to store and retrieve all the settings for a single pad.
 The program should contain 48 objects of this class, one for each pad.
 The class just contains a set of accessor and mutator meothods for each of the classes variables.
 */

//NOTE: WHEN APPLYING SETTINGS INTO HERE FROM XML FILES (PROBABLY BY CALLING THE MUTATOR METHODS) SOMETIMES IT MIGHT TRY AND SET VALUES IN OBJECTS THAT DON'T EXIST.
//IN THIS CASE IT MAY BE A GOOD IDEA TO PASS IN DATA FROM LOOPER MODE AND SEQUENCE MODE TO KEEP THIS CLASS KNOWING AND UPDATED AT WHAT OBJECTS EXIST OR NOT, AND ONLY APPLY THE SETTINGS IF THEY EXIST (IF OBJECT[PAD] != NULL)
//what settings should be saved into and loaded from xmls files? how should it handle the data on the pads that isn't need yet (e.g. the seq data if the pad is noe set to a looper)?
//don;t want unncessary data loaded up when switching between presets.

#include "../../JuceLibraryCode/JuceHeader.h"
#include "../Functionality Classes/Sampler Mode/ModeLooper.h"
#include "../Functionality Classes/Sequencer Mode/SequencerValues.h"

class AlphaLiveEngine;
class AppSettings;
 
class PadSettings
{
public:
    //==================================================================
    PadSettings (int arrayIndex);
    ~PadSettings();
    
    void setAlphaLiveEngineRef (AlphaLiveEngine *ref);
    void setPadNumber (int value);
    void resetData(int whatToReset);
    
    //==================================================================
    //==================================================================
    //==================================================================
    
    //==================================================================
    //Global
    void setMode (int value);
    void setCurrentState (int value);
    void setCurrentPlayingState (int value);
    void setCurrentValue (int value); 
    void setPressureSensitivityMode (int value);
    void setExclusiveMode (int value);
    void setExclusiveGroup (int value);
    void setQuantizeMode (int value);

    int getMode();
    int getCurrentState();
    int getCurrentValue();
    int getCurrentPlayingState();
    int getPressureSensitivityMode();
    int getExclusiveMode();
    int getExclusiveGroup();
    int getQuantizeMode();
    
    //==================================================================
    //MIDI mode
    void setMidiNote (int value);
    void setMidiVelocity (int value);
    void setMidiChannel (int value);
    void setMidiMinPressureRange (int value);
    void setMidiMaxPressureRange (int value);
    void setMidiPressureMode (int value);
    void setMidiTriggerMode (int value);
    void setMidiIndestructible (int value);
    void setMidiSticky (int value);
    void setMidiPressureStatus (bool value);
    void setMidiNoteStatus (bool value);
    void setMidiCcController (int value);
    void setMidiExclusiveGroup (int value);
    void setMidiQuantizeMode (int value);
    
    int getMidiNote();
    int getMidiVelocity();
    int getMidiChannel();
    int getMidiMinPressureRange();
    int getMidiMaxPressureRange();
    int getMidiPressureMode();
    int getMidiTriggerMode();
    int getMidiIndestructible();
    int getMidiSticky();
    bool getMidiPressureStatus();
    bool getMidiNoteStatus();
    int getMidiCcController();
    int getMidiExclusiveGroup();
    int getMidiQuantizeMode();
    
    //==================================================================
    //Looper mode
    void setLooperAudioFilePath (File value);
    void setLooperTriggerMode (int value);
    void setLooperShouldLoop (int value);
    void setLooperIndestructible (int value);
    void setLooperShouldFinishLoop (int value);
    void setLooperSticky (int value);
    void setLooperEffect (int value);
    void setLooperPan (float value);
    void setLooperGain (float value);
    void setLooperChannel (int value);
    void setLooperQuantizeMode (int value);
    
    File getLooperAudioFilePath();
    bool getLooperIsLibraryFile();
    int getLooperTriggerMode();
    int getLooperShouldLoop();
    int getLooperIndestructible();
    int getLooperShouldFinishLoop();
    int getLooperSticky();
    int getLooperEffect();
    float getLooperPan();
    float getLooperGain();
    int getLooperChannel();
    int getLooperQuantizeMode();
    
    //----Looper FX----
    //Gain&Pan
    void setLooperFxGainPanGain (float value);
    void setLooperFxGainPanPan (float value);
    void setLooperFxGainPanAlphaTouch (int value);
    void setLooperFxGainPanAtReverse (int value);
    void setLooperFxGainPanAtIntensity (float value);
    float getLooperFxGainPanGain();
    float getLooperFxGainPanPan();
    int getLooperFxGainPanAlphaTouch();
    int getLooperFxGainPanAtReverse();
    float getLooperFxGainPanAtIntensity();
    //LPF
    void setLooperFxLpfMix (float value);
    void setLooperFxLpfFreq (float value);
    void setLooperFxLpfBandwidth (float value);
    void setLooperFxLpfAlphaTouch (int value);
    void setLooperFxLpfAtReverse (int value);
    void setLooperFxLpfAtIntensity (float value);
    float getLooperFxLpfMix();
    float getLooperFxLpfFreq();
    float getLooperFxLpfBandwidth();
    int getLooperFxLpfAlphaTouch();
    int getLooperFxLpfAtReverse();
    float getLooperFxLpfAtIntensity();
    //HPF
    void setLooperFxHpfMix (float value);
    void setLooperFxHpfFreq (float value);
    void setLooperFxHpfBandwidth (float value);
    void setLooperFxHpfAlphaTouch (int value);
    void setLooperFxHpfAtReverse (int value);
    void setLooperFxHpfAtIntensity (float value);
    float getLooperFxHpfMix();
    float getLooperFxHpfFreq();
    float getLooperFxHpfBandwidth();
    int getLooperFxHpfAlphaTouch();
    int getLooperFxHpfAtReverse();
    float getLooperFxHpfAtIntensity();
    //BPF
    void setLooperFxBpfMix (float value);
    void setLooperFxBpfFreq (float value);
    void setLooperFxBpfBandwidth (float value);
    void setLooperFxBpfAlphaTouch (int value);
    void setLooperFxBpfAtReverse (int value);
    void setLooperFxBpfAtIntensity (float value);
    float getLooperFxBpfMix();
    float getLooperFxBpfFreq();
    float getLooperFxBpfBandwidth();
    int getLooperFxBpfAlphaTouch();
    int getLooperFxBpfAtReverse();
    float getLooperFxBpfAtIntensity();
    //delay
    void setLooperFxDelayMix (float value);
    void setLooperFxDelayTime (float value);
    void setLooperFxDelayFeedback (float value);
    void setLooperFxDelayLpfFreq (float value);
    void setLooperFxDelayHpfFreq (float value);
    void setLooperFxDelaySync (int value);
    void setLooperFxDelayTimeMenu (int value);
    void setLooperFxDelayAlphaTouch (int value);
    void setLooperFxDelayAtReverse (int value);
    void setLooperFxDelayAtIntensity (float value);
    float getLooperFxDelayMix();
    float getLooperFxDelayTime();
    float getLooperFxDelayFeedback();
    float getLooperFxDelayLpfFreq();
    float getLooperFxDelayHpfFreq();
    int getLooperFxDelaySync();
    int getLooperFxDelayTimeMenu();
    int getLooperFxDelayAlphaTouch();
    int getLooperFxDelayAtReverse();
    float getLooperFxDelayAtIntensity();
    //reverb
    void setLooperFxReverbMix (float value);
    void setLooperFxReverbRoomSize (float value);
    void setLooperFxReverbDamping (float value);
    void setLooperFxReverbWidth (float value);
    void setLooperFxReverbFreezeMode (float value);
    void setLooperFxReverbAlphaTouch (int value);
    void setLooperFxReverbAtReverse (int value);
    void setLooperFxReverbAtIntensity (float value);
    float getLooperFxReverbMix();
    float getLooperFxReverbRoomSize();
    float getLooperFxReverbDamping();
    float getLooperFxReverbWidth();
    float getLooperFxReverbFreezeMode();
    int getLooperFxReverbAlphaTouch();
    int getLooperFxReverbAtReverse();
    float getLooperFxReverbAtIntensity();
    //flanger
    void setLooperFxFlangerMix (double value);
    void setLooperFxFlangerRate(double value);
    void setLooperFxFlangerFeedback (double value);
    void setLooperFxFlangerIntensity (double value);
    void setLooperFxFlangerSync (int value);
    void setLooperFxFlangerRateMenu (int value);
    void setLooperFxFlangerAlphaTouch (int value);
    void setLooperFxFlangerAtReverse (int value);
    void setLooperFxFlangerAtIntensity (double value);
    double getLooperFxFlangerMix();
    double getLooperFxFlangerRate();
    double getLooperFxFlangerFeedback();
    double getLooperFxFlangerIntensity();
    int getLooperFxFlangerSync();
    int getLooperFxFlangerRateMenu();
    int getLooperFxFlangerAlphaTouch();
    int getLooperFxFlangerAtReverse();
    double getLooperFxFlangerAtIntensity();
    //tremolo
    void setLooperFxTremoloDepth (double value);
    void setLooperFxTremoloRate (double value);
    void setLooperFxTremoloShape (int value);
    void setLooperFxTremoloSync (int value);
    void setLooperFxTremoloRateMenu (int value);
    void setLooperFxTremoloAlphaTouch (int value);
    void setLooperFxTremoloAtReverse (int value);
    void setLooperFxTremoloAtIntensity (double value);
    double getLooperFxTremoloDepth();
    double getLooperFxTremoloRate();
    int getLooperFxTremoloShape();
    int getLooperFxTremoloSync();
    int getLooperFxTremoloRateMenu();
    int getLooperFxTremoloAlphaTouch();
    int getLooperFxTremoloAtReverse();
    double getLooperFxTremoloAtIntensity();
    
    
    //==================================================================
    //Sequencer mode
    void setSequencerMode (int value);
    void setSequencerData (int sequenceNumber, int rowNumber, int columnNumber, int value, bool shouldUpdateSeqDataString=true);
    void setSequencerNumberOfSequences (int value);
    void setSequencerTriggerMode (int value);
    void setSequencerShouldLoop (int value);
    void setSequencerIndestructible (int value);
    void setSequencerShouldFinishLoop (int value);
    void setSequencerSticky (int value);
    void setSequencerChannel (int value);
    void setSequencerLength (int value);
    void setSequencerQuantizeMode (int value);
    void setSequencerRelativeTempoMode (int value);
    void setSequencerDynamicMode (int value);
    
    void setSequencerMidiNote (int value, int arrayIndex);
    void setSequencerMidiVelocity (int value); //NO LONGER NEED THIS
    void setSequencerMidiChannel (int value);
    void setSequencerMidiNoteLength (int value);
    void setSequencerMidiMinPressureRange (int value);
    void setSequencerMidiMaxPressureRange (int value);
    void setSequencerMidiPressureMode (int value);
    void setSequencerMidiPressureStatus (bool value);
    void setSequencerMidiCcController (int value);
    
    void setSequencerSamplesAudioFilePath (File value, int sequencerRow);
    void setSequencerPan (float value);
    void setSequencerGain (float value);
    
    int getSequencerMode();
    int getSequencerData (int sequenceNumber, int rowNumber, int columnNumber);
    int getSequencerNumberOfSequences();
    int getSequencerTriggerMode();
    int getSequencerShouldLoop();
    int getSequencerIndestructible();
    int getSequencerShouldFinishLoop();
    int getSequencerSticky();
    int getSequencerChannel();
    int getSequencerLength();
    int getSequencerQuantizeMode();
    int getSequencerRelativeTempoMode();
    int getSequencerDynamicMode();
    
    int getSequencerMidiNote(int arrayIndex);
    int getSequencerMidiVelocity(); //NO LONGER NEED THIS
    int getSequencerMidiChannel();
    int getSequencerMidiNoteLength();
    int getSequencerMidiMinPressureRange();
    int getSequencerMidiMaxPressureRange();
    int getSequencerMidiPressureMode();
    bool getSequencerMidiPressureStatus();
    int getSequencerMidiCcController();
    
    File getSequencerSamplesAudioFilePath (int sequencerRow);
    bool getSequencerIsLibraryFile (int sequencerRow);
    float getSequencerPan();
    float getSequencerGain();
    
    //used to encode the sequence data into a more friendly form for saving to xml
    void seqDataToString();
    void stringToSeqData (String savedString, int seqNumber);
    void stringToSeqDataFormatConversion (String savedString, int seqNumber);   //function for converting seq data of the old 
                                                                                //format to the new format
                                                                       
    String getSequencerDataString (int seqNumber);
    void clearSequencerDataString (int seqNumber);
    
    //see private members section below for notes on other needed Sequencer methods
    
    //==================================================================
    //Controller Mode
    void setControllerControl (int value);
    void setControllerPresetNumber (int value);
    void setControllerOscIpAddress (String value);
    void setControllerOscPort (int value);
    void setControllerMidiProgramChangeNumber (int value);
    void setControllerMidiProgramChangeChannel (int value);
    
    int getControllerControl();
    int getControllerPresentNumber();
    String getControllerOscIpAddress();
    int getControllerOscPort();
    int getControllerMidiProgramChangeNumber();
    int getControllerMidiProgramChangeChannel();

    
    //==================================================================
    //==================================================================
    //==================================================================
    
private:
    
    int padNumber; //this should be private surely?! Test it out
    AlphaLiveEngine *alphaLiveEngineRef;
    
    //==================================================================
    //Global
    int mode; // 0 = off, 1 = midi, 2 = looper, 3 = sequencer, 4 = controller
    int prevMode;
    int currentState; //Hods the current physical state. 1 = pressed, 0 = not pressed
    int currentPlayingState; //Holds the current PLAYING state. 0 = off, 1 = on
    int currentValue; //Holds the current modified pressire value
    
    int pressureSensitivityMode;
    int exclusiveMode;
    int exclusiveGroup;
    int quantizeMode;
    
    //==================================================================
    //MIDI mode
    int midiNote;
    int midiVelocity;
    int midiChannel;
    int midiMinPressureRange;
    int midiMaxPressureRange;
    int midiPressureMode;
    int midiTriggerMode;
    int midiIndestructible;
    int midiSticky;
    bool midiPressureStatus;
    bool midiNoteStatus;
    int midiCcController;
    //int midiExclusiveGroup;
    //int midiQuantizeMode;
    
    //==================================================================
    //Looper mode
    String looperAudioFilePath;
    int looperTriggerMode;
    int looperShouldLoop;
    int looperIndestructible;
    int looperShouldFinishLoop;
    int looperSticky;
    int looperEffect;
    float looperPan;
    float looperGain;
    //int looperChannel; //now called 'group' not 'channel' to the user
    //int looperQuantizeMode;
    
    //----fx variables------
    //Gain&Pan
    float looperFxGainPanGain;
    float looperFxGainPanPan;
    int looperFxGainPanAlphaTouch;
    int looperFxGainPanAtReverse;
    float looperFxGainPanAtIntensity;
    //LPF
    float looperFxLpfMix;
    float looperFxLpfFreq;
    float looperFxLpfBandwidth;
    int looperFxLpfAlphaTouch;
    int looperFxLpfAtReverse;
    float looperFxLpfAtIntensity;
    //HPF
    float looperFxHpfMix;
    float looperFxHpfFreq;
    float looperFxHpfBandwidth;
    int looperFxHpfAlphaTouch;
    int looperFxHpfAtReverse;
    float looperFxHpfAtIntensity;
    //BPF
    float looperFxBpfMix;
    float looperFxBpfFreq;
    float looperFxBpfBandwidth;
    int looperFxBpfAlphaTouch;
    int looperFxBpfAtReverse;
    float looperFxBpfAtIntensity;
    //Delay
    float looperFxDelayMix;
    float looperFxDelayTime;
    float looperFxDelayFeedback;
    float looperFxDelayLpfFreq;
    float looperFxDelayHpfFreq;
    int looperFxDelaySync;
    int looperFxDelayTimeMenu;
    int looperFxDelayAlphaTouch;
    int looperFxDelayAtReverse;
    float looperFxDelayAtIntensity;
    
    //Reverb
    float looperFxReverbMix;
    float looperFxReverbRoomSize;
    float looperFxReverbDamping;
    float looperFxReverbWidth;
    float looperFxReverbFreezeMode;
    int looperFxReverbAlphaTouch;
    int looperFxReverbAtReverse;
    float looperFxReverbAtIntensity;
    
    //Flanger
    double looperFxFlangerMix;
    double looperFxFlangerRate;
    double looperFxFlangerFeedback;
    double looperFxFlangerIntensity;
    int looperFxFlangerSync;
    int looperFxFlangerRateMenu;
    int looperFxFlangerAlphaTouch;
    int looperFxFlangerAtReverse;
    double looperFxFlangerAtIntensity;
    
    //Tremolo
    double looperFxTremoloDepth;
    double looperFxTremoloRate;
    int looperFxTremoloShape;
    int looperFxTremoloSync;
    int looperFxTremoloRateMenu;
    int looperFxTremoloAlphaTouch;
    int looperFxTremoloAtReverse;
    float looperFxTremoloAtIntensity;
    
    
    
    
    //==================================================================
    //Sequencer mode
    int sequencerMode; //Midi or Samples
    int sequencerData[NO_OF_SEQS][NO_OF_ROWS][NO_OF_COLUMNS]; //[sequence][row][column]
    int sequencerNumberOfSequences;
    int sequencerTriggerMode;
    int sequencerShouldLoop;
    int sequencerIndestructible;
    int sequencerShouldFinishLoop;
    int sequencerSticky;
    //int sequencerChannel; //now called 'group' not 'channel' to the user
    int sequencerLength;
    //int sequencerQuantizeMode;
    int sequencerRelativeTempoMode;
    int sequencerDynamicMode;
    
    int sequencerMidiNote[NO_OF_ROWS]; //assuming there are 12 rows to a sequencer
    int sequencerMidiVelocity; //NO LONGER NEED THIS
    int sequencerMidiChannel;
    int sequencerMidiNoteLength;
    int sequencerMidiMinPressureRange;
    int sequencerMidiMaxPressureRange;
    int sequencerMidiPressureMode;
    int sequencerMidiCcController;
    bool sequencerMidiPressureStatus;
    
    String sequencerSamplesAudioFilePath[NO_OF_ROWS];
    float sequencerPan;
    float sequencerGain;
    
    //this is the sequence data variable that is saved to xml, NOT the 3D int array above!
    String sequencerDataString[NO_OF_SEQS];
    
    
    //possible extra settings - gain and pan for each individual samples
    
    //==================================================================
    //Controller Mode
    int controllerControl; //type of control
    int controllerPresetNumber; //if control is set to preset switcher, this selects the preset number
    String controllerOscIpAddress;
    int controllerOscPort;
    int controllerMidiProgramChangeNumber;
    int controllerMidiProgramChangeChannel;
    
};


#endif // H_PADSETTINGS



