//
//  GuiSamplerMode.cpp
//  AlphaSoft
//
//  Created by Liam Meredith-Lacey on 25/09/2011.
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

#include "GuiSamplerMode.h"
#include "../../File and Settings/AppSettings.h"
#include "../Binary Data/ImageSliderBinaryData.h"
#include "GlobalValues.h"
#include "MainComponent.h"

#define PAD_SETTINGS AppSettings::Instance()->padSettings[padNum]
#define SINGLE_PAD (selectedPads.size() == 1)
#define MULTI_PADS (selectedPads.size() > 1)

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

GuiSamplerMode::GuiSamplerMode(MainComponent &ref)
: mainComponentRef(ref)
										
{
    
    //----------------quantise button-------------------
	
	addAndMakeVisible(quantiseButton = new AlphaTextButton("Q"));
	quantiseButton->setClickingTogglesState(true);
	quantiseButton->setToggleState(false, false);	
	quantiseButton->addListener(this);
	quantiseButton->addMouseListener(this, true);
	quantiseButton->setOpaque(false);
	
	
	//----------------trigger settings button-------------------
	
	addAndMakeVisible(triggerSettingsButton = new AlphaTextButton("TRIGGER"));
	triggerSettingsButton->setRadioGroupId (1234);
	triggerSettingsButton->setClickingTogglesState(true);
	triggerSettingsButton->setToggleState(false, false);	
	triggerSettingsButton->addListener(this);
	triggerSettingsButton->addMouseListener(this, true);
	triggerSettingsButton->setOpaque(false);
    triggerSettingsButton->setToggleState(true, false);
	
	//----------------pressure settings button-------------------
	
	addAndMakeVisible(pressureSettingsButton = new AlphaTextButton("PRESSURE"));
	pressureSettingsButton->setRadioGroupId (1234);
	pressureSettingsButton->setClickingTogglesState(true);
	pressureSettingsButton->setToggleState(false, false);	
	pressureSettingsButton->addListener(this);
	pressureSettingsButton->addMouseListener(this, true);
	pressureSettingsButton->setOpaque(false);

    
    addAndMakeVisible (waveform = new DemoThumbnailComp());
	waveform->setInterceptsMouseClicks(false, false);
    
    
    fileChooser = new FilenameComponent ("audiofile",
										 File::nonexistent,
										 false, false, false,
										 "*.wav; *.aif; *.aiff",
										 String::empty,
										 "(choose a WAV or AIFF file)");
	fileChooser->addListener (this);					
	fileChooser->setBrowseButtonText ("+");
	fileChooser->setMaxNumberOfRecentFiles (20);
	addAndMakeVisible (fileChooser);
    fileChooser->addMouseListener(this, true);
    
    /*
    //create gain slider
    addAndMakeVisible(gainSlider = new AlphaImageKnob(2));
    gainSlider->sliderComponent()->setRange(0.0, 2.0);
    gainSlider->sliderComponent()->addListener(this);
	gainSlider->sliderComponent()->setValue(0.7, false);
    gainSlider->sliderComponent()->addMouseListener(this, true);
	
	//create pan slider
    addAndMakeVisible(panSlider = new AlphaImageKnob(2, true));
    panSlider->sliderComponent()->setRange(0.0, 1.0);
    panSlider->sliderComponent()->addListener(this);
    panSlider->sliderComponent()->setValue(0.5, false);
    panSlider->sliderComponent()->addMouseListener(this, true);
     */

    /*
    addAndMakeVisible(triggerModeMenu = new ComboBox());
    triggerModeMenu->addListener(this);
    triggerModeMenu->addItem("Hold", 1);
    triggerModeMenu->addItem("Toggle", 2);
    triggerModeMenu->addItem("Toggle Release", 3);
    triggerModeMenu->addItem("Latch", 4);
    triggerModeMenu->addItem("Latch Max", 5);
    triggerModeMenu->addItem("Trigger", 6);
    triggerModeMenu->setSelectedId(2, true);
    triggerModeMenu->addMouseListener(this, true);
     */
    
    //----------------------Trigger mode buttons------------------
    for (int i = 0; i < 4; i++)
    {
        if (i == 0)
            triggerModeButtons.insert(i, new SettingsButton("STANDARD", (270 * (M_PI / 180)), 
                                                            (315 * (M_PI / 180)),
                                                            0.4f, -90, 0.45, 0.75));
        else if (i == 1)
            triggerModeButtons.insert(i, new SettingsButton("TOGGLE", (315 * (M_PI / 180)),
                                                            (2 * M_PI) , 0.4f, -90, 0.45, 0.68));
        else if (i == 2)
            triggerModeButtons.insert(i, new SettingsButton("LATCH", 0.0f, (45 * (M_PI / 180)), 
                                                            0.4f, 90, 0.55, 0.3));
        else if (i == 3)
            triggerModeButtons.insert(i, new SettingsButton("TRIGGER", (45 * (M_PI / 180)), 
                                                            (90 * (M_PI / 180)), 0.4f, 90, 0.55, 0.25));
        
        triggerModeButtons[i]->addListener(this);
        triggerModeButtons[i]->setOpaque(false);
        triggerModeButtons[i]->setRadioGroupId (43);
        triggerModeButtons[i]->addMouseListener(this, false);
        addAndMakeVisible(triggerModeButtons[i]);
    }
    
    triggerModeButtons[1]->setToggleState(true, false);
    
    addAndMakeVisible(loopButton = new AlphaTextButton("Loop"));
    loopButton->addListener(this);
    loopButton->addMouseListener(this, true);
    loopButton->setClickingTogglesState(true);
    loopButton->setToggleState(1, false);
    
    addAndMakeVisible(indestructibleButton = new AlphaTextButton("indestruct"));
    indestructibleButton->addListener(this);
    indestructibleButton->addMouseListener(this, true);
    indestructibleButton->setClickingTogglesState(true);
    indestructibleButton->setToggleState(0, false);
    
    addAndMakeVisible(finishLoopButton = new AlphaTextButton("Finish"));
    finishLoopButton->addListener(this);
    finishLoopButton->addMouseListener(this, true);
    finishLoopButton->setClickingTogglesState(true);
    finishLoopButton->setToggleState(0, false);
    
    addChildComponent(fxDial = new GuiFxDial(mainComponentRef));
	fxDial->setInterceptsMouseClicks(false, true);
    fxDial->addMouseListener(this, false);
    
    addChildComponent(stickyButton = new AlphaTextButton("Sticky"));
    stickyButton->addListener(this);
    stickyButton->addMouseListener(this, true);
    stickyButton->setClickingTogglesState(true);
    stickyButton->setToggleState(0, false);
    
    
    //---------------status off bg-------------------------------------
    addAndMakeVisible(notSelected = new GuiCircleBackground());
	//notSelected->setInterceptsMouseClicks(false, false);
	notSelected->setVisible(false);
	
	//---------------pressure status button-------------------------------------
    
    addAndMakeVisible(pressureStatusButton = new GuiSwitch());
    pressureStatusButton->addListener(this);
    pressureStatusButton->setClickingTogglesState(true);
    pressureStatusButton->setToggleState(true, false);
    pressureStatusButton->addMouseListener(this, false);
    
}


GuiSamplerMode::~GuiSamplerMode()
{
    
    //deleteAllChildren();
    
}


void GuiSamplerMode::resized()
{
    notSelected->setBounds(0, 0, getWidth(), getHeight());
	pressureStatusButton->setBounds(816, 393, 58, 58);
	
    waveform->setBounds(683, 261, 324, 324);
	
    fileChooser->setBounds(787, 393, 116, 80);
	
	quantiseButton->setBounds(681, 288,32, 32);
	triggerSettingsButton->setBounds(789, 221,42, 42);
	pressureSettingsButton->setBounds(847, 219,42, 42);
	
	triggerModeButtons[0]->setBounds(728, 305, 234, 234);
	triggerModeButtons[1]->setBounds(728, 305, 234, 234);
	triggerModeButtons[2]->setBounds(728, 305, 234, 234);
	triggerModeButtons[3]->setBounds(728, 305, 234, 234);
	
	loopButton->setBounds(894, 472,32, 32);
	indestructibleButton->setBounds(853, 496,32, 32);
	finishLoopButton->setBounds(918, 431,32, 32);
	
	stickyButton->setBounds(853, 496,32, 32);
	
    // gainSlider->setBounds(845, 495, 45, 45);
	//panSlider->setBounds(900, 495, 45, 45);
    
    fxDial->setBounds(683, 261, 324, 324);

}

void GuiSamplerMode::paint (Graphics& g)
{
    float xBrowseButton = 787 + (116 * 0.25);
	float yBrowseButton = 393;
	float widthBrowseButton = 58;
	
	
	ColourGradient fillGradient(AlphaColours::nearlyblack,845 , 461, Colours::black, 845 , 383, false);
	g.setGradientFill(fillGradient);
	
	g.fillEllipse(802, 379, 86, 86);
	
	g.setColour(Colours::black);
	
	g.fillEllipse(786,218, 48, 48);
	g.fillEllipse(844,216, 48, 48);
	
	g.fillEllipse(678,285, 38, 38);
	g.fillEllipse(850,493, 38, 38);
	
	if(triggerSettingsButton->getToggleStateValue()==true)
	{
        g.fillEllipse(891,469, 38, 38);
        g.fillEllipse(915,428, 38, 38);
		
		Path pieSeg;
        pieSeg.addPieSegment(802, 379, 86, 86, (125 * (M_PI / 180)), (235 * (M_PI / 180)), 0.2f);
        g.fillPath(pieSeg);
	}
	
	
	
	g.fillEllipse(xBrowseButton, yBrowseButton, widthBrowseButton, widthBrowseButton);
	
	g.setColour(Colours::grey.withAlpha(0.3f));
	
	g.drawEllipse(678,285, 38, 38, 1.0);
	g.drawEllipse(850,493, 38, 38, 1.0);
	
	if(triggerSettingsButton->getToggleStateValue()==true)
	{
        g.drawEllipse(891,469, 38, 38, 1.0);
        g.drawEllipse(915,428, 38, 38, 1.0);
	}
	
	g.drawEllipse((xBrowseButton + (widthBrowseButton * 0.1)), (yBrowseButton + (widthBrowseButton * 0.1)),
				  (widthBrowseButton * 0.8),(widthBrowseButton * 0.8), 1.0f);
}




void GuiSamplerMode::comboBoxChanged (ComboBox* comboBox)
{
    


}


void GuiSamplerMode::sliderValueChanged (Slider* slider)
{
    /*
    //==============================================================================
    //gain slider
    if (slider == gainSlider->sliderComponent())
    {
        for (int i = 0; i < selectedPads.size(); i++)
        {
            int padNum = selectedPads[i];
            PAD_SETTINGS->setSamplerGain(gainSlider->sliderComponent()->getValue());
        }
    }
    
    //==============================================================================
    //pan slider
    if (slider == panSlider->sliderComponent())
    {
        for (int i = 0; i < selectedPads.size(); i++)
        {
            int padNum = selectedPads[i];
            PAD_SETTINGS->setSamplerPan(panSlider->sliderComponent()->getValue());
        }
        
    }
        //==============================================================================
     */

}


void GuiSamplerMode::filenameComponentChanged (FilenameComponent* filenameComponent)
{
    if (filenameComponent == fileChooser)
    {
        // this is called when the user changes the filename in the file chooser box
        File audioFile (filenameComponent->getCurrentFile().getFullPathName());
        
        if(audioFile.existsAsFile())
        {
            for (int i = 0; i < selectedPads.size(); i++)
            {
                int padNum = selectedPads[i];
                PAD_SETTINGS->setSamplerAudioFilePath(audioFile);
				
				waveform->setFile (audioFile);
				
            }
            
        }
        
        else
        {
            AlertWindow::showMessageBox (AlertWindow::WarningIcon,
                                         "AlphaLive",
                                         "Couldn't open file!\n\n");
        }	
    }
    
}





void GuiSamplerMode::buttonClicked (Button* button)
{
    if(button == triggerSettingsButton)
		setDisplay(1);        
    
	
	else if(button == pressureSettingsButton)
        setDisplay(2);
    
    
    else if (button == loopButton)
    {
        for (int i = 0; i < selectedPads.size(); i++)
        {
            int padNum = selectedPads[i];
            PAD_SETTINGS->setSamplerShouldLoop(button->getToggleState());
        }
    }
    
    else if (button == indestructibleButton)
    {
        for (int i = 0; i < selectedPads.size(); i++)
        {
            int padNum = selectedPads[i];
            PAD_SETTINGS->setSamplerIndestructible(button->getToggleState());
        }
    }
    
    else if (button == finishLoopButton)
    {
        for (int i = 0; i < selectedPads.size(); i++)
        {
            int padNum = selectedPads[i];
            PAD_SETTINGS->setSamplerShouldFinishLoop(button->getToggleState());
        }
    }
    else if (button == stickyButton)
    {
        for (int i = 0; i < selectedPads.size(); i++)
        {
            int padNum = selectedPads[i];
            PAD_SETTINGS->setSamplerSticky(button->getToggleState());
        }
    }
    
    
    else if(button == pressureStatusButton)
	{
        for (int i = 0; i < selectedPads.size(); i++)
        {
            int padNum = selectedPads[i];
            
            if (button->getToggleState() == false)
            {
                PAD_SETTINGS->setSamplerEffect(0);
            }
            else if (button->getToggleState() == true)
            {
                PAD_SETTINGS->setSamplerEffect(1); //set default effect
                fxDial->updateDisplay();
            }
                
            
            //PAD_SETTINGS->setSamplerPressureStatus(button->getToggleState());
        }
        
        if(pressureStatusButton->getToggleStateValue()==true)
            notSelected->setVisible(false);
        else
            notSelected->setVisible(true);
		
	}
    
    
    //triggerMode buttons
    for (int trig = 0; trig < 4; trig++)
    {
        if (button == triggerModeButtons[trig])
        {
            for (int i = 0; i < selectedPads.size(); i++)
            {
                int padNum = selectedPads[i];
                PAD_SETTINGS->setSamplerTriggerMode(trig);
            }
            
            break;
        }
    }
}



void GuiSamplerMode::setDisplay(int settingsType)
{
    if (settingsType == 1) //trigger settings
    {
        
        waveform->setVisible(true);
        fileChooser->setVisible(true);
        
        for (int i = 0; i < 4; i++)
            triggerModeButtons[i]->setVisible(true);
        
        loopButton->setVisible(true);
        indestructibleButton->setVisible(true);
        finishLoopButton->setVisible(true);
        
        
        fxDial->setVisible(false);
        pressureStatusButton->setVisible(false);
        notSelected->setVisible(false);
        stickyButton->setVisible(false);
        
        repaint(750, 200, 274, 469); 
        
    }
    
    else if (settingsType == 2) //pressure settings
    {
        
        waveform->setVisible(false);
        fileChooser->setVisible(false);
        
        for (int i = 0; i < 4; i++)
            triggerModeButtons[i]->setVisible(false);
        
        loopButton->setVisible(false);
        indestructibleButton->setVisible(false);
        finishLoopButton->setVisible(false);
        
        fxDial->setVisible(true);
        pressureStatusButton->setVisible(true);
        stickyButton->setVisible(true);
        
        if(pressureStatusButton->getToggleStateValue()==true)
            notSelected->setVisible(false);
        else
            notSelected->setVisible(true);
        
        repaint(750, 200, 274, 469);
        
        
    }
    
}


void GuiSamplerMode::setCurrentlySelectedPad (Array<int> selectedPads_)
{
    selectedPads = selectedPads_;
    fxDial->setCurrentlySelectedPad(selectedPads);
}

void GuiSamplerMode::updateDisplay()
{
    
    //This method is used to set all the components to the currently selected pad's settings,
    //as well as to hide/dissabled any unneeded components. 
    
    //if an individual pad number is currently selected
    if (SINGLE_PAD)
    {
        int padNum = selectedPads[0];
        
        fileChooser->setCurrentFile(PAD_SETTINGS->getSamplerAudioFilePath(), true, false);
		File audioFile(PAD_SETTINGS->getSamplerAudioFilePath());
		waveform->setFile (audioFile);
		
        //gainSlider->sliderComponent()->setValue(PAD_SETTINGS->getSamplerGain(), false);
        //panSlider->sliderComponent()->setValue(PAD_SETTINGS->getSamplerPan(), false);
        triggerModeButtons[PAD_SETTINGS->getSamplerTriggerMode()]->setToggleState(true, false);
        loopButton->setToggleState(PAD_SETTINGS->getSamplerShouldLoop(), false);
        indestructibleButton->setToggleState(PAD_SETTINGS->getSamplerIndestructible(), false);
        finishLoopButton->setToggleState(PAD_SETTINGS->getSamplerShouldFinishLoop(), false);
        stickyButton->setToggleState(PAD_SETTINGS->getSamplerSticky(), false);
        
        if (PAD_SETTINGS->getSamplerEffect() == 0)
            pressureStatusButton->setToggleState(false, false);
        else
            pressureStatusButton->setToggleState(true, false);
    }

    else if (MULTI_PADS)
    {
        
        //set default values
        fileChooser->setCurrentFile(File::nonexistent, false, false);
        waveform->setFile (File::nonexistent);
        //gainSlider->sliderComponent()->setValue(0.7, false);
        //panSlider->sliderComponent()->setValue(0.5, false);
        triggerModeButtons[0]->setToggleState(true, false); //ideally nothing should be selected here
        loopButton->setToggleState(1, false);
        indestructibleButton->setToggleState(0, false);
        finishLoopButton->setToggleState(0, false);
        stickyButton->setToggleState(0, false);
        pressureStatusButton->setToggleState(false, false);
    }

    
    //set visibility of certain components
    
    notSelected->setVisible(false);
    
    if (triggerSettingsButton->getToggleState() == true)
        setDisplay(1);
    else if (pressureSettingsButton->getToggleState() == true)
        setDisplay(2);
    
    
    fxDial->updateDisplay();
}



void GuiSamplerMode::mouseEnter (const MouseEvent &e)
{
    /*
    if (fileChooser->isMouseOver(true))
    {
        mainComponentRef.setInfoTextBoxText("Audio File Selector. Sets and displays the filepath name of the audio file for the selected pad/pads. Use the '+' button to open a File Browser Window, or use the drop-down menu to select from recently selected files, as well as view the currently selected file.");
    }
    else if (panSlider->isMouseOver(true))
    {
        mainComponentRef.setInfoTextBoxText("Pan Knob. Sets and displays the panning/stereo positioning of the selected pad/pads audio signal.");
    }
    else if (gainSlider->isMouseOver(true))
    {
        mainComponentRef.setInfoTextBoxText("Gain Knob. Sets and displays the gain/volume of the selected pad/pads audio signal.");
    }
    else if (triggerModeMenu->isMouseOver(true))
    {
        mainComponentRef.setInfoTextBoxText("TriggerMode Drop-down Menu. \nSets and displays the sampler TriggerMode for the selected pad/pads. Sampler TriggerModes determine how interation with a pad controls the playback and modification of an audio file.");
    }
    else if (fxDial->isMouseOver(true))
    {
        mainComponentRef.setInfoTextBoxText("Sampler FX Dial. Sets and displays the audio processing effect that the selected pad/pads pressure controls.");
    }
     */
    
}

void GuiSamplerMode::mouseExit (const MouseEvent &e)
{
    //remove any text
    mainComponentRef.setInfoTextBoxText (String::empty);
}

