//
//  FxGuiBandPassFilter.cpp
//  AlphaLive
//
//  Created by Liam Meredith-Lacey on 20/12/2011.
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

#include "FxGuiBandPassFilter.h"
#include "../../../../File and Settings/AppSettings.h"
#include "../../../Views/MainComponent.h"
//#include "../../../AlphaLiveLookandFeel.h"

#define PAD_SETTINGS AppSettings::Instance()->padSettings[padNum]
#define SINGLE_PAD (selectedPads.size() == 1)
#define MULTI_PADS (selectedPads.size() > 1)


GuiBandPassFilter::GuiBandPassFilter(MainComponent &ref)
: mainComponentRef(ref)
{
    addAndMakeVisible(mixSlider = new AlphaRotarySlider((250 * (M_PI / 180)), (470 * (M_PI / 180)), 130));
	mixSlider->setRotaryParameters((250 * (M_PI / 180)), (470 * (M_PI / 180)),true);
    mixSlider->setRange(0.0, 1.0);
    mixSlider->setValue(1.0, false);
    mixSlider->addListener(this);
    mixSlider->addMouseListener(this, true);
    
	addAndMakeVisible(frequencySlider = new AlphaRotarySlider((250 * (M_PI / 180)), (470 * (M_PI / 180)), 150));
	frequencySlider->setRotaryParameters((250 * (M_PI / 180)), (470 * (M_PI / 180)),true);
    frequencySlider->setRange(30, 20000, 1);
    frequencySlider->setValue(1000, false);
    frequencySlider->addListener(this);
    frequencySlider->addMouseListener(this, true);
    
    addAndMakeVisible(bandwidthSlider = new AlphaRotarySlider((250 * (M_PI / 180)), (470 * (M_PI / 180)), 170));
	bandwidthSlider->setRotaryParameters((250 * (M_PI / 180)), (470 * (M_PI / 180)),true);
    bandwidthSlider->setRange(0.0, 100.0);
    bandwidthSlider->setValue(5, false);
    bandwidthSlider->addListener(this);
    bandwidthSlider->addMouseListener(this, true);
    
    addAndMakeVisible(alphaTouchMenu = new ComboBox());
    alphaTouchMenu->addListener(this);
    alphaTouchMenu->addMouseListener(this, true);
    alphaTouchMenu->addItem("Off", 1);
    alphaTouchMenu->addItem("Mix", 2);
    alphaTouchMenu->addItem("Cut-Off Frequency", 3);
    alphaTouchMenu->addItem("Bandwidth/Resonance", 4);
    alphaTouchMenu->setSelectedId(1, true);
    
    addAndMakeVisible(reverseButton = new AlphaTextButton("INVERT"));
    reverseButton->setClickingTogglesState(true);
    reverseButton->addListener(this);
    reverseButton->addMouseListener(this, true);
    
    addAndMakeVisible(intensitySlider = new AlphaRotarySlider((250 * (M_PI / 180)), (470 * (M_PI / 180)), 190));
	intensitySlider->setRotaryParameters((250 * (M_PI / 180)), (470 * (M_PI / 180)),true);
    intensitySlider->setRange(0.0, 1.0);
    intensitySlider->setValue(1.0, false);
    intensitySlider->addListener(this);
    intensitySlider->addMouseListener(this, true);
    intensitySlider->setColour(Slider::rotarySliderFillColourId, AlphaColours::lightblue);
    
    
    setInterceptsMouseClicks(false, true);
}

GuiBandPassFilter::~GuiBandPassFilter()
{
    deleteAllChildren();
}



void GuiBandPassFilter::resized()
{
    mixSlider->setBounds(97, 97, 130, 130);
    frequencySlider->setBounds(87, 87, 150, 150);
    bandwidthSlider->setBounds(77, 77, 170, 170);
	intensitySlider->setBounds(67, 67, 190, 190);
    
    alphaTouchMenu->setBounds(119, 192, 87, 20);
    reverseButton->setBounds(211,211, 32, 32);
}



void GuiBandPassFilter::sliderValueChanged (Slider *slider)
{
    if (slider == mixSlider)
    {
        for (int i = 0; i < selectedPads.size(); i++)
        {
            int padNum = selectedPads[i];
            PAD_SETTINGS->setSamplerFxBpfMix(mixSlider->getValue());
        }
    }
    
    
    if (slider == frequencySlider)
    {
        for (int i = 0; i < selectedPads.size(); i++)
        {
            int padNum = selectedPads[i];
            PAD_SETTINGS->setSamplerFxBpfFreq(frequencySlider->getValue());
        }
        
    }
    
    
    if (slider == bandwidthSlider)
    {
        for (int i = 0; i < selectedPads.size(); i++)
        {
            int padNum = selectedPads[i];
            PAD_SETTINGS->setSamplerFxBpfBandwidth(bandwidthSlider->getValue());
        }
        
    }
    
    
    if (slider == intensitySlider)
    {
        for (int i = 0; i < selectedPads.size(); i++)
        {
            int padNum = selectedPads[i];
            PAD_SETTINGS->setSamplerFxBpfAtIntensity(intensitySlider->getValue());
        }
    }
    
    
}

void GuiBandPassFilter::comboBoxChanged (ComboBox *comboBox)
{
    if (comboBox == alphaTouchMenu)
    {
        for (int i = 0; i < selectedPads.size(); i++)
        {
            int padNum = selectedPads[i];
            PAD_SETTINGS->setSamplerFxBpfAlphaTouch(alphaTouchMenu->getSelectedId());
        }
    }
    
}


void GuiBandPassFilter::buttonClicked (Button *button)
{
    if (button == reverseButton)
    {
        for (int i = 0; i < selectedPads.size(); i++)
        {
            int padNum = selectedPads[i];
            PAD_SETTINGS->setSamplerFxBpfAtReverse(reverseButton->getToggleState());
        }
        
    }
}

void GuiBandPassFilter::setCurrentlySelectedPad (Array<int> selectedPads_)
{
    selectedPads = selectedPads_;
}

void GuiBandPassFilter::updateDisplay()
{
    //This method is used to set all the components to the currently selected pad's settings.
    
    //if an individual pad number is currently selected
    if(SINGLE_PAD)
    {
        int padNum = selectedPads[0];
        mixSlider->setValue(PAD_SETTINGS->getSamplerFxBpfMix(), false);
        frequencySlider->setValue(PAD_SETTINGS->getSamplerFxBpfFreq(), false);
        bandwidthSlider->setValue(PAD_SETTINGS->getSamplerFxBpfBandwidth(), false);
        alphaTouchMenu->setSelectedId(PAD_SETTINGS->getSamplerFxBpfAlphaTouch(), true);
        reverseButton->setToggleState(PAD_SETTINGS->getSamplerFxBpfAtReverse(), false);
        intensitySlider->setValue(PAD_SETTINGS->getSamplerFxBpfAtIntensity(), false);
    }
    
    else if(MULTI_PADS)
    {
        mixSlider->setValue(1.0, false);
        frequencySlider->setValue(1000, false);
        bandwidthSlider->setValue(5.0, false);
        alphaTouchMenu->setSelectedId(1, true);
        reverseButton->setToggleState(0, false);
        intensitySlider->setValue(1.0, false);
    }
    
}

void GuiBandPassFilter::mouseEnter (const MouseEvent &e)
{
    if (mixSlider->isMouseOver(true))
    {
        mainComponentRef.setInfoTextBoxText("Band-Pass Filter Mix Control. Sets the wet/dry ratio for Band-Pass filter for the selected pad/pads.");
    }
    else if (frequencySlider->isMouseOver(true))
    {
        mainComponentRef.setInfoTextBoxText("Band-Pass Filter Centre Frequency Control. Sets the centre frequency for Band-Pass filter for the selected pad/pads.");
    }
    else if (bandwidthSlider->isMouseOver(true))
    {
        mainComponentRef.setInfoTextBoxText("Band-Pass Filter Bandwidth Control. Sets the bandwidth for Band-Pass filter for the selected pad/pads.");
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

void GuiBandPassFilter::mouseExit (const MouseEvent &e)
{
    //remove any text
    mainComponentRef.setInfoTextBoxText (String::empty);
    
}