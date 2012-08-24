//
//  GuiGlobalClock.cpp
//  AlphaLive
//
//  Created by Liam Meredith-Lacey on 09/02/2012.
//  Copyright 2012 nu desine.
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

#include "GuiGlobalClock.h"
#include "../Views/MainComponent.h"
#include "../../File and Settings/AppSettings.h"
#include "AlphaLiveLookandFeel.h"
#include "../../Application/CommonInfoBoxText.h"

#define OFFSET_X 479
#define OFFSET_Y 6


GuiGlobalClock::GuiGlobalClock(MainComponent &ref, AlphaLiveEngine &ref2)
:   mainComponentRef(ref),
    alphaLiveEngineRef(ref2)
{
    mainComponentRef.getAlphaLiveEngineRef().getGlobalClock()->attach(this);
    
    //tempo slider (IncDecButtons)
    addAndMakeVisible(tempoSlider = new AlphaSlider());
    tempoSlider->setRange(60.0, 360.0, 0.1);
    tempoSlider->addListener(this);
    tempoSlider->setComponentValue(120.0);
    tempoSlider->addMouseListener(this, true);
	
	//beats per bar buttons
    for (int i = 0; i < 6; i++)
    {
        beatsPerBarButtons.insert(i, new AlphaTextButton(String(i+2)));
        beatsPerBarButtons[i]->setClickingTogglesState(true);
        beatsPerBarButtons[i]->addListener(this);
        beatsPerBarButtons[i]->addMouseListener(this, true);
        beatsPerBarButtons[i]->setRadioGroupId (1234);
        
        addAndMakeVisible(beatsPerBarButtons[i]);
    }
	
    beatsPerBarButtons[2]->setToggleState(true, false);
	
	//quantisation buttons
    for (int i = 0; i < 6; i++)
    {
        if (i == 0)
           quantizationValueButtons.insert(i, new SettingsButton("1/4", (238.5 * (M_PI / 180)), (268.5 * (M_PI / 180)), 0.75f, -10, 0.2, 0.28)); 
        else if (i == 1)
            quantizationValueButtons.insert(i, new SettingsButton("1/2", (268.5 * (M_PI / 180)), (298.5 * (M_PI / 180)), 0.75f, -5, 0.2, 0.28));
        else if (i == 2)
            quantizationValueButtons.insert(i, new SettingsButton("1", (298.5 * (M_PI / 180)), (328.5 * (M_PI / 180)), 0.75f, 0, 0.4, 0.28));
        else if (i == 3)
            quantizationValueButtons.insert(i, new SettingsButton("1", (333.5 * (M_PI / 180)), (356 * (M_PI / 180)), 0.75f, -3, 0.38, 0.28));
        else if (i == 4)
            quantizationValueButtons.insert(i, new SettingsButton("2", (356 * (M_PI / 180)), (378.5 * (M_PI / 180)), 0.75f, 0, 0.4, 0.28));
        else if (i == 5)
            quantizationValueButtons.insert(i, new SettingsButton("4", (378.5 * (M_PI / 180)), (401 * (M_PI / 180)), 0.75f, 0, 0.4, 0.28));
        
        quantizationValueButtons[i]->addListener(this);
        quantizationValueButtons[i]->addMouseListener(this, false);
        quantizationValueButtons[i]->setRadioGroupId (43);
        addAndMakeVisible(quantizationValueButtons[i]);
        
    }
    
    quantizationValueButtons[3]->setToggleState(true, false);
    
    
    
    //transport button
	addAndMakeVisible(transportButton = new AlphaTextButton());
    transportButton->setButtonText(translate("START"));
    transportButton->setClickingTogglesState(true);
    transportButton->setToggleState(false, false);
    transportButton->addListener(this);
    transportButton->addMouseListener(this, true);
	
	
     /*
     //auto-start switch
     addAndMakeVisible(autoStartSwitch = new GuiSwitch());
     autoStartSwitch->addListener(this);
     autoStartSwitch->setClickingTogglesState(true);
     autoStartSwitch->setToggleState(false, false);
     autoStartSwitch->addMouseListener(this, true);
     */
    
	currentBeatNumber = 0;
	currentBeatStore = 0;
	
	countGap = (4 * (M_PI / 180));
	countSeg = 0;
	segStart = 0;
	segEnd = 0;
    
    
    
}

GuiGlobalClock::~GuiGlobalClock()
{
    beatsPerBarButtons.clear();
    quantizationValueButtons.clear();
    
    deleteAllChildren();
    //delete animator;
    
    //detach this class from the subject class
    mainComponentRef.getAlphaLiveEngineRef().getGlobalClock()->detach(this);
}

void GuiGlobalClock::resized()
{
    transportButton->setBounds(644-OFFSET_X, 42, 56, 56);
    tempoSlider->setBounds(550-OFFSET_X, 12, 50, 50);
	
	beatsPerBarButtons[0]->setBounds(631-OFFSET_X, 111, 17, 17);
	beatsPerBarButtons[1]->setBounds(659-OFFSET_X, 121, 17, 17);
	beatsPerBarButtons[2]->setBounds(689-OFFSET_X, 115, 17, 17);
	beatsPerBarButtons[3]->setBounds(712-OFFSET_X, 95, 17, 17);
	beatsPerBarButtons[4]->setBounds(722-OFFSET_X, 67, 17, 17);
	beatsPerBarButtons[5]->setBounds(716-OFFSET_X, 37, 17, 17);
	
    for (int i = 0; i < 6; i++)
        quantizationValueButtons[i]->setBounds(606-OFFSET_X, 6, 131, 131);
	
}

void GuiGlobalClock::paint (Graphics &g)
{
	
    quantiseBg.clear(); // <- without this, the CPU level slowly increases.
	barsBg.clear();
    
	quantiseBg.addPieSegment(603-OFFSET_X, 3, 137, 137, (235.5 * (M_PI / 180)), (404 * (M_PI / 180)), 0.5f);
	
	g.setColour(Colours::black);
	g.fillPath(quantiseBg, getTransform());
	
	g.setColour(Colours::grey.withAlpha(0.2f));
	g.fillEllipse(634-OFFSET_X, 32, 76, 76);
	
	barsBg.addPieSegment(626-OFFSET_X, 24, 93, 93, 0, (90 * (M_PI / 180)), 0.5f);
	barsBg.addPieSegment(626-OFFSET_X, 24, 93, 93, (180 * (M_PI / 180)), (270 * (M_PI / 180)), 0.5f);
	g.setColour(Colours::grey.withAlpha(0.2f));
	g.fillPath(barsBg, getTransform());
	
	g.setColour(Colours::black);
	g.fillEllipse(639-OFFSET_X, 37, 66, 66);
	
    //in the below call should I get the AppSettings::Instance()->getBeatsPerBar() value from a local variable instead
    //which is set everytime the beats per bar value is changed in order to reduce CPU?
	countSeg = ((M_PI/2) - (countGap * AppSettings::Instance()->getBeatsPerBar())) / AppSettings::Instance()->getBeatsPerBar();
	
	if (currentBeatNumber == 1) 
    {
		barCount.clear();
		
		segStart = countGap * 0.5;
		segEnd = segStart + countSeg;
		
		barCount.addPieSegment(627-OFFSET_X, 26, 90, 90, segStart, segEnd, 0.9f);
	}
	
	if (currentBeatNumber != currentBeatStore && currentBeatNumber != 1)
	{
		segStart = segEnd + countGap;
		segEnd = segStart + countSeg;
		
		barCount.addPieSegment(627-OFFSET_X, 26, 90, 90, segStart, segEnd, 0.9f);
        
		currentBeatStore = currentBeatNumber;	
	}	
	
	g.setColour(AlphaColours::blue);
	g.fillPath(barCount, getTransform());
    
	
}


bool GuiGlobalClock::update(const Subject& theChangedSubject)
{
    if (&theChangedSubject == mainComponentRef.getAlphaLiveEngineRef().getGlobalClock())
    {
        //if beat indicator needs updating
        if (mainComponentRef.getAlphaLiveEngineRef().getGlobalClock()->getGuiUpdateFlag() == 1)
        {
            //update the beat label number
            //beatNumberLabel->setText(String(mainComponentRef.getOscRoutingRef().getGlobalClock()->getBeatNumber()), true);
            int beat = mainComponentRef.getAlphaLiveEngineRef().getGlobalClock()->getBeatNumber();
            //update the bar label number
            //barNumberLabel->setText(String(mainComponentRef.getOscRoutingRef().getGlobalClock()->getBarNumber()), true);
            int bar = mainComponentRef.getAlphaLiveEngineRef().getGlobalClock()->getBarNumber();
			
			currentBeatNumber = (bar * beat) + (beat -1);
			
            repaint(606-OFFSET_X, 6, 131, 131);
        }
        //if transport button needs updating
        else if (mainComponentRef.getAlphaLiveEngineRef().getGlobalClock()->getGuiUpdateFlag() == 2)
        {
            transportButton->setToggleState(true, false);
            transportButton->setButtonText(translate("STOP"));
        }
    }
	
    return true;
}

void GuiGlobalClock::sliderValueChanged (Slider* slider)
{
    if (slider == tempoSlider)
    {
        AppSettings::Instance()->setGlobalTempo(tempoSlider->getValue());
    }
}

void GuiGlobalClock::buttonClicked (Button* button)
{
    
    for (int i = 0; i < 6; i++)
    {
       if (button == beatsPerBarButtons[i]) 
           AppSettings::Instance()->setBeatsPerBar(i+2);
        
        else if(button == quantizationValueButtons[i])
            AppSettings::Instance()->setQuantizationValue(6-i);
    }
    
	
    if (button == transportButton)
    {
        if (transportButton->getToggleState() == true)
        {
            alphaLiveEngineRef.getGlobalClock()->startClock();
            transportButton->setButtonText(translate("STOP"));
            mainComponentRef.setIsClockRunning(true);
        }
        else
        {
            alphaLiveEngineRef.getGlobalClock()->stopClock();
            transportButton->setButtonText(translate("START"));
            mainComponentRef.setIsClockRunning(false);
        }
    }
    
    /*
     else if (button == autoStartSwitch)
     {
     if (autoStartSwitch->getToggleState() == true)
     {
     AppSettings::Instance()->setAutoStartClock(1);
     }
     else
     AppSettings::Instance()->setAutoStartClock(0);
     
     }
     */
}

void GuiGlobalClock::comboBoxChanged(ComboBox *comboBox)
{
    
}

void GuiGlobalClock::toggleTransportButtonOff()
{
    if (transportButton->getToggleState() == true)
    {
        transportButton->setToggleState(false, false);
        transportButton->setButtonText(translate("START"));
        mainComponentRef.setIsClockRunning(false);
    }
    
}

void GuiGlobalClock::triggerTransportButton()
{
    transportButton->triggerClick();
}

void GuiGlobalClock::updateDisplay()
{
    tempoSlider->setComponentValue(AppSettings::Instance()->getGlobalTempo());
	
    beatsPerBarButtons[AppSettings::Instance()->getBeatsPerBar()-2]->setToggleState(true, false);
    quantizationValueButtons[6-AppSettings::Instance()->getQuantizationValue()]->setToggleState(true, false);

}

void GuiGlobalClock::mouseEnter (const MouseEvent &e)
{
    if (tempoSlider->isMouseOver(true))
    {
        mainComponentRef.setInfoTextBoxText (translate("Global Tempo Selector. Sets and displays the tempo that controls the playback speed of the global clock and any sequences."));
    }
    
    else if (transportButton->isMouseOver(true))
    {
        mainComponentRef.setInfoTextBoxText (translate("Clock Start/Stop Button. Use this button to manually start and stop the global clock."));
    }
    /*
     else if (autoStartSwitch->isMouseOver(true))
     {
     mainComponentRef.setInfoTextBoxText ("Clock Auto-Start Switch. If set to true the clock will automatically start the first time a loop or sequence is played, else the clock will need to be manually started using the Start/Stop button.");
     }
     */
    
    else if (quantizationValueButtons[0]->isMouseOver(true))
    {
        mainComponentRef.setInfoTextBoxText (translate("Quarter Beat Quantization Value.") + " " + translate(CommonInfoBoxText::quantizationValueButtons));
    }
    
    else if (quantizationValueButtons[1]->isMouseOver(true))
    {
        mainComponentRef.setInfoTextBoxText (translate("Half Beat Quantization Value.") + " " + translate(CommonInfoBoxText::quantizationValueButtons));
    }
    else if (quantizationValueButtons[2]->isMouseOver(true))
    {
       mainComponentRef.setInfoTextBoxText (translate("One Beat Quantization Value.") + " " + translate(CommonInfoBoxText::quantizationValueButtons));
    }
    else if (quantizationValueButtons[3]->isMouseOver(true))
    {
        mainComponentRef.setInfoTextBoxText (translate("One Bar Quantization Value.") + " " + translate(CommonInfoBoxText::quantizationValueButtons));
    }
    else if (quantizationValueButtons[4]->isMouseOver(true))
    {
        mainComponentRef.setInfoTextBoxText (translate("Two Bars Quantization Value.") + " " + translate(CommonInfoBoxText::quantizationValueButtons));
    }
    else if (quantizationValueButtons[5]->isMouseOver(true))
    {
        mainComponentRef.setInfoTextBoxText (translate("Four Bars Quantization Value.") + " " + translate(CommonInfoBoxText::quantizationValueButtons));
    }
    
    for (int i = 0; i < 6; i++)
    {
        if (beatsPerBarButtons[i]->isMouseOver(true))
        {
            mainComponentRef.setInfoTextBoxText (String (i+2) + " " + translate("Beats-Per-Bar. This set of buttons allows a basic time signature for the global clock to be set."));
        }
    }
    

}

void GuiGlobalClock::mouseExit (const MouseEvent &e)
{
    //remove any text
    mainComponentRef.setInfoTextBoxText (String::empty);
}
