//
//  FxGuiTremolo.cpp
//  AlphaLive
//
//  Created by Liam Meredith-Lacey on 13/07/2012.
//  Copyright 2012 nu desine.
//
//  Created by Liam Meredith-Lacey on 10/07/2012.
//  Copyright 2012 nu desine. All rights reserved.
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

#include "FxGuiTremolo.h"
#include "../../../../File and Settings/AppSettings.h"
#include "../../../Views/MainComponent.h"

#define PAD_SETTINGS AppSettings::Instance()->padSettings[padNum]
#define SINGLE_PAD (selectedPads.size() == 1)
#define MULTI_PADS (selectedPads.size() > 1)


GuiTremolo::GuiTremolo(MainComponent &ref)
:           mainComponentRef(ref)
{
    addAndMakeVisible(depthSlider = new AlphaRotarySlider((250 * (M_PI / 180)), (470 * (M_PI / 180)), 130));
	depthSlider->setRotaryParameters((250 * (M_PI / 180)), (470 * (M_PI / 180)),true);
    depthSlider->setRange(0.0, 1.0);
    depthSlider->setValue(0.7, false);
    depthSlider->addListener(this);
    depthSlider->addMouseListener(this, true);
    
	addAndMakeVisible(rateSlider = new AlphaRotarySlider((250 * (M_PI / 180)), (470 * (M_PI / 180)), 150));
	rateSlider->setRotaryParameters((250 * (M_PI / 180)), (470 * (M_PI / 180)),true);
    rateSlider->setRange(0, 50.0);
    rateSlider->setValue(5.0, false);
    rateSlider->addListener(this);
    rateSlider->addMouseListener(this, true);
    
    addAndMakeVisible(intensitySlider = new AlphaRotarySlider((250 * (M_PI / 180)), (470 * (M_PI / 180)), 170));
	intensitySlider->setRotaryParameters((250 * (M_PI / 180)), (470 * (M_PI / 180)),true);
    intensitySlider->setRange(0.0, 1.0);
    intensitySlider->setValue(0.5, false);
    intensitySlider->addListener(this);
    intensitySlider->addMouseListener(this, true);
    intensitySlider->setColour(Slider::rotarySliderFillColourId, AlphaColours::lightblue);
    
    
    addAndMakeVisible(rateMenu = new ComboBox());
    rateMenu->addListener(this);
    rateMenu->addMouseListener(this, true);
    rateMenu->addItem("1/1", 1);
    rateMenu->addItem("1/2", 2);
    rateMenu->addItem("1/4", 3);
    rateMenu->addItem("1/8", 4);
    rateMenu->addItem("1/16", 5);
    rateMenu->addItem("1/32", 6);
    rateMenu->addItem("1/64", 7);
    //what about other values, such as the d's and t's in Logic's tremolo?
    rateMenu->setSelectedId(3, true);
    
    addAndMakeVisible(syncButton = new AlphaTextButton("SYNC"));
    syncButton->setClickingTogglesState(true);
    syncButton->setToggleState(1, false);
    syncButton->addListener(this);
    syncButton->addMouseListener(this, true);
    
    addAndMakeVisible(shapeMenu = new ComboBox());
    shapeMenu->addListener(this);
    shapeMenu->addMouseListener(this, true);
    shapeMenu->addItem("Sine", 1);
    shapeMenu->addItem("Square", 2);
    shapeMenu->addItem("Triangle", 3);
    shapeMenu->addItem("Rising Sawtooth", 4);
    shapeMenu->addItem("Falling Sawtooth", 5);
    shapeMenu->setSelectedId(1, true);
    
    
    addAndMakeVisible(alphaTouchMenu = new ComboBox());
    alphaTouchMenu->addListener(this);
    alphaTouchMenu->addMouseListener(this, true);
    alphaTouchMenu->addItem("Off", 1);
    alphaTouchMenu->addItem("Depth/Mix", 2);
    alphaTouchMenu->addItem("Rate", 3);
    alphaTouchMenu->addItem("Wave Shape", 4);
    alphaTouchMenu->setSelectedId(1, true);
    
    addAndMakeVisible(reverseButton = new AlphaTextButton("INVERT"));
    reverseButton->setClickingTogglesState(true);
    reverseButton->addListener(this);
    reverseButton->addMouseListener(this, true);
    
    tempo = AppSettings::Instance()->getGlobalTempo();
    
    setInterceptsMouseClicks(false, true);
}

GuiTremolo::~GuiTremolo()
{
    deleteAllChildren();
}



void GuiTremolo::resized()
{
    //this needs rearranging
    //maybe the sync button going above the rate menu.
    //and the sticky and invert button are spaced equally at the bottom (should be applied to every effect)
    //with the shape menu central under the alphatouch menu
    
    depthSlider->setBounds(97, 97, 130, 130);
    rateSlider->setBounds(87, 87, 150, 150);
    intensitySlider->setBounds(77, 77, 170, 170);
    
    alphaTouchMenu->setBounds(119, 192, 87, 20);
    reverseButton->setBounds(211,211, 32, 32);
    
    rateMenu->setBounds(119, 52, 87, 20);
    shapeMenu->setBounds(80, 213, 87, 20);
    syncButton->setBounds(130, 235, 32, 32);
    

}



void GuiTremolo::sliderValueChanged (Slider *slider)
{
    if (slider == depthSlider)
    {
        for (int i = 0; i < selectedPads.size(); i++)
        {
            int padNum = selectedPads[i];
            PAD_SETTINGS->setSamplerFxTremoloDepth(depthSlider->getValue());
        }
        
    }
    
    else if (slider == rateSlider)
    {
        for (int i = 0; i < selectedPads.size(); i++)
        {
            int padNum = selectedPads[i];
            PAD_SETTINGS->setSamplerFxTremoloRate(rateSlider->getValue());
        }
        
    }
    
    
    else if (slider == intensitySlider)
    {
        for (int i = 0; i < selectedPads.size(); i++)
        {
            int padNum = selectedPads[i];
            PAD_SETTINGS->setSamplerFxTremoloAtIntensity(intensitySlider->getValue());
        }
        
    }
    
    
    
}

void GuiTremolo::comboBoxChanged (ComboBox *comboBox)
{
    if (comboBox == alphaTouchMenu)
    {
        for (int i = 0; i < selectedPads.size(); i++)
        {
            int padNum = selectedPads[i];
            PAD_SETTINGS->setSamplerFxTremoloAlphaTouch(alphaTouchMenu->getSelectedId());
        }
        
    }
    
    else if (comboBox == shapeMenu)
    {
        for (int i = 0; i < selectedPads.size(); i++)
        {
            int padNum = selectedPads[i];
            PAD_SETTINGS->setSamplerFxTremoloShape(shapeMenu->getSelectedId());
        }
        
    }
    
    else if (comboBox == rateMenu)
    {
        //work out LFO rate based on rate selected and the tempo.
        tempo = AppSettings::Instance()->getGlobalTempo();
        double bps = tempo/60.0;
        double lfoRate;
        
        switch (rateMenu->getSelectedId())
        {
                
            case 1: // 1/1 - 4 beats
                lfoRate = bps * 0.25;
                break;
            case 2: // 1/2 - 2 beats
                lfoRate = bps * 0.5;
                break;
            case 3: // 1/4 - 1 beat
                lfoRate = bps * 1.0;
                break;
            case 4: // 1/8 - half beat
                lfoRate = bps * 2.0;
                break;
            case 5: // 1/16 - quarter beat
                lfoRate = bps * 4.0;
                break;
            case 6: // 1/32 - 8th beat
                lfoRate = bps * 8.0;
                break;
            case 7: // 1/64 - 16th beat
                lfoRate = bps * 16.0;
                break;
            default: // 1/4 - 1 beat
                lfoRate = bps * 1.0;
                break;
                 
        }
        
        rateSlider->setValue(lfoRate, false);
        
        for (int i = 0; i < selectedPads.size(); i++)
        {
            int padNum = selectedPads[i];
            PAD_SETTINGS->setSamplerFxTremoloRate(lfoRate);
            PAD_SETTINGS->setSamplerFxTremoloRateMenu(rateMenu->getSelectedId());
        }
        
    }
    
}


void GuiTremolo::buttonClicked (Button *button)
{
    if (button == reverseButton)
    {
        for (int i = 0; i < selectedPads.size(); i++)
        {
            int padNum = selectedPads[i];
            PAD_SETTINGS->setSamplerFxTremoloAtReverse(reverseButton->getToggleState());
        }
        
    }
    
    else if (button == syncButton)
    {
        for (int i = 0; i < selectedPads.size(); i++)
        {
            int padNum = selectedPads[i];
            PAD_SETTINGS->setSamplerFxTremoloSync(syncButton->getToggleState());
        }
        
        rateSlider->setVisible(false);
        rateMenu->setVisible(false);
        
        if (syncButton->getToggleState() == 0) //off
            rateSlider->setVisible(true);
        else //on
            rateMenu->setVisible(true);
        
    }
}

void GuiTremolo::setCurrentlySelectedPad (Array<int> selectedPads_)
{
    selectedPads = selectedPads_;
}

void GuiTremolo::updateDisplay()
{
    //This method is used to set all the components to the currently selected pad's settings.
    rateSlider->setVisible(false);
    rateMenu->setVisible(false);
    
    //if an individual pad number is currently selected
    if(SINGLE_PAD)
    {
        int padNum = selectedPads[0];
        depthSlider->setValue(PAD_SETTINGS->getSamplerFxTremoloDepth(), false);
        rateSlider->setValue(PAD_SETTINGS->getSamplerFxTremoloRate(), false);
        rateMenu->setSelectedId(PAD_SETTINGS->getSamplerFxTremoloRateMenu(), true);
        syncButton->setToggleState(PAD_SETTINGS->getSamplerFxTremoloSync(), false);
        shapeMenu->setSelectedId(PAD_SETTINGS->getSamplerFxTremoloShape(), true);
        
        alphaTouchMenu->setSelectedId(PAD_SETTINGS->getSamplerFxTremoloAlphaTouch(), true);
        reverseButton->setToggleState(PAD_SETTINGS->getSamplerFxTremoloAtReverse(), false);
        intensitySlider->setValue(PAD_SETTINGS->getSamplerFxTremoloAtIntensity(), false);
    }
    
    else if(MULTI_PADS)
    {
        depthSlider->setValue(0.7, false);
        rateSlider->setValue(5.0, false);
        rateMenu->setSelectedId(3, true);
        syncButton->setToggleState(true, false);
        shapeMenu->setSelectedId(2, true);
        
        alphaTouchMenu->setSelectedId(1, true);
        reverseButton->setToggleState(0, false);
        intensitySlider->setValue(1.0, false);
    }
    
    
    if (syncButton->getToggleState() == 0) //off
        rateSlider->setVisible(true);
    else //on
        rateMenu->setVisible(true);
    
}

//need this?? not currently being used
void GuiTremolo::setTempo (float value)
{
    tempo = value;
    //OR
    tempo = AppSettings::Instance()->getGlobalTempo();
}

void GuiTremolo::mouseEnter (const MouseEvent &e)
{
    if (depthSlider->isMouseOver(true))
    {
        mainComponentRef.setInfoTextBoxText("Depth/Mix Control. Sets the depth/mix of the LFO for the selected pad/pads.");
    }
    else if (rateSlider->isMouseOver(true))
    {
        mainComponentRef.setInfoTextBoxText("LFO Rate Control. Sets the rate in Hz for the selected pad/pads. If you would like to set the rate based on the tempo, click on the 'Tempo Sync' button.");
    }
    else if (rateMenu->isMouseOver(true))
    {
        mainComponentRef.setInfoTextBoxText("LFO Rate Menu. Sets the LFO rate for the selected pad/pads. If you would like to set the rate in Hz, click on the 'Tempo Sync' button.");
    }
    else if (syncButton->isMouseOver(true))
    {
        mainComponentRef.setInfoTextBoxText("Tempo Sync Button. Turn this button on to sync the LFO to the tempo, else you can set the LFO is Hz.");
    }
    else if (shapeMenu->isMouseOver(true))
    {
        mainComponentRef.setInfoTextBoxText("Waveshape Menu. Sets the LFO waveshape for the selected pad/pads.");
    }
    else if (alphaTouchMenu->isMouseOver(true))
    {
        mainComponentRef.setInfoTextBoxText("AlphaTouch Menu. Sets the effect parameter that the pads pressure will control for the selected pad/pads.");
    }
    else if (reverseButton->isMouseOver(true))
    {
        mainComponentRef.setInfoTextBoxText("AlphaTouch Reverse Button. Activate this button to reverse/invert the direction of the modulated created by the pressure of the selected pad/pads.");
    }
    else if (intensitySlider->isMouseOver(true))
    {
        mainComponentRef.setInfoTextBoxText("AlphaTouch Intensity Control. Sets the intensity/range of modulation created by the pressure of the selected pad/pads.");
    }
    
}

void GuiTremolo::mouseExit (const MouseEvent &e)
{
    //remove any text
    mainComponentRef.setInfoTextBoxText (String::empty);
    
}
