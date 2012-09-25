//
//  FxGuiDistortion.cpp
//  AlphaLive
//
//  Created by Felix Godden on the 25/09/2012
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

#include "FxGuiDistortion.h"
#include "../../../../File and Settings/AppSettings.h"
#include "../../../Views/MainComponent.h"
#include "../../../Binary Data/BinaryDataNew.h"
#include "../../../../Application/CommonInfoBoxText.h"

#define PAD_SETTINGS AppSettings::Instance()->padSettings[padNum]
#define SINGLE_PAD (selectedPads.size() == 1)
#define MULTI_PADS (selectedPads.size() > 1)


GuiDistortion::GuiDistortion(MainComponent &ref)
:           mainComponentRef(ref)
{
    addAndMakeVisible(inputGainSlider = new AlphaRotarySlider((250 * (M_PI / 180)), (470 * (M_PI / 180)), 130));
	depthSlider->setRotaryParameters((250 * (M_PI / 180)), (470 * (M_PI / 180)),true);
    depthSlider->setRange(0.0, 1.0);
    depthSlider->setValue(0.7, false);
    depthSlider->addListener(this);
    depthSlider->addMouseListener(this, true);
    
	addAndMakeVisible(driveSlider = new AlphaRotarySlider((250 * (M_PI / 180)), (470 * (M_PI / 180)), 150));
	rateSlider->setRotaryParameters((250 * (M_PI / 180)), (470 * (M_PI / 180)),true);
    rateSlider->setRange(0, 50.0);
    rateSlider->setValue(5.0, false);
    rateSlider->addListener(this);
    rateSlider->addMouseListener(this, true);
	
	addAndMakeVisible(driveSlider = new AlphaRotarySlider((250 * (M_PI / 180)), (470 * (M_PI / 180)), 150));
	rateSlider->setRotaryParameters((250 * (M_PI / 180)), (470 * (M_PI / 180)),true);
    rateSlider->setRange(0, 50.0);
    rateSlider->setValue(5.0, false);
    rateSlider->addListener(this);
    rateSlider->addMouseListener(this, true);
	
	addAndMakeVisible(outputGainSlider = new AlphaRotarySlider((250 * (M_PI / 180)), (470 * (M_PI / 180)), 150));
	rateSlider->setRotaryParameters((250 * (M_PI / 180)), (470 * (M_PI / 180)),true);
    rateSlider->setRange(0, 50.0);
    rateSlider->setValue(5.0, false);
    rateSlider->addListener(this);
    rateSlider->addMouseListener(this, true);
	
	addAndMakeVisible(wetDryMixSlider = new AlphaRotarySlider((250 * (M_PI / 180)), (470 * (M_PI / 180)), 150));
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
    
    
    addAndMakeVisible(distortionTypeMenu = new ComboBox());
    distortionTypeMenu->addListener(this);
    distortionTypeMenu->addMouseListener(this, true);
    distortionTypeMenu->addItem("Soft", 1);
    distortionTypeMenu->addItem("Hard", 2);
    distortionTypeMenu->addItem("HF0", 3);
    distortionTypeMenu->addItem("HF1", 4);
    distortionTypeMenu->addItem("HF2", 5);
    distortionTypeMenu->addItem("Digital", 6);
    distortionTypeMenu->setSelectedId(1, true);
    
    addAndMakeVisible(syncButton = new AlphaTextButton(translate("SYNC")));
    syncButton->setClickingTogglesState(true);
    syncButton->setToggleState(1, false);
    syncButton->addListener(this);
    syncButton->addMouseListener(this, true);
    
    addAndMakeVisible(shapeMenu = new ComboBox());
    shapeMenu->addListener(this);
    shapeMenu->addMouseListener(this, true);
    shapeMenu->addItem(translate("Sine"), 1);
    shapeMenu->addItem(translate("Square"), 2);
    shapeMenu->addItem(translate("Triangle"), 3);
    shapeMenu->addItem(translate("Rising Sawtooth"), 4);
    shapeMenu->addItem(translate("Falling Sawtooth"), 5);
    shapeMenu->setSelectedId(1, true);
    
    
    addAndMakeVisible(alphaTouchMenu = new ComboBox());
    alphaTouchMenu->addListener(this);
    alphaTouchMenu->addMouseListener(this, true);
    alphaTouchMenu->addItem(translate("Off"), 1);
    alphaTouchMenu->addItem(translate("Depth/Mix"), 2);
    alphaTouchMenu->addItem(translate("Rate"), 3);
    alphaTouchMenu->addItem(translate("Wave Shape"), 4);
    alphaTouchMenu->setSelectedId(1, true);
    
    Image *reverseIcon = new Image(ImageCache::getFromMemory(BinaryDataNew::inverticon_png, BinaryDataNew::inverticon_pngSize));
    addAndMakeVisible(reverseButton = new ModeButton(reverseIcon));
    reverseButton->setClickingTogglesState(true);
    reverseButton->addListener(this);
    reverseButton->addMouseListener(this, true);
    
    //---------------parameter label -------------------------------------
    addAndMakeVisible(parameterHoverLabel = new Label("value label", String::empty));
    parameterHoverLabel->setJustificationType(Justification::centred);
    parameterHoverLabel->setColour(Label::textColourId, AlphaColours::blue);
    parameterHoverLabel->setFont(Font(9));
    parameterHoverLabel->addMouseListener(this, true);
    
    tempo = AppSettings::Instance()->getGlobalTempo();
    
    setInterceptsMouseClicks(false, true);
}

GuiDistortion::~GuiDistortion()
{
    deleteAllChildren();
}



void GuiDistortion::resized()
{
    //this needs rearranging
    //maybe the sync button going above the rate menu.
    //and the sticky and invert button are spaced equally at the bottom (should be applied to every effect)
    //with the shape menu central under the alphatouch menu
    
    depthSlider->setBounds(97, 97, 130, 130);
    rateSlider->setBounds(87, 87, 150, 150);
    intensitySlider->setBounds(77, 77, 170, 170);
    
    alphaTouchMenu->setBounds(119, 202, 87, 15);
    reverseButton->setBounds(211,211, 32, 32);
    parameterHoverLabel->setBounds(144, 187, 36, 15);
    
    rateMenu->setBounds(119, 52, 87, 20);
    shapeMenu->setBounds(80, 218, 87, 15);
    syncButton->setBounds(130, 235, 32, 32);
    
	
}



void GuiDistortion::sliderValueChanged (Slider *slider)
{
    if (slider == depthSlider)
    {
        for (int i = 0; i < selectedPads.size(); i++)
        {
            int padNum = selectedPads[i];
            PAD_SETTINGS->setPadFxDistortionDepth(depthSlider->getValue());
        }
        
        parameterHoverLabel->setText(String(slider->getValue(), 3), false);
        
    }
    
    else if (slider == rateSlider)
    {
        for (int i = 0; i < selectedPads.size(); i++)
        {
            int padNum = selectedPads[i];
            PAD_SETTINGS->setPadFxDistortionRate(rateSlider->getValue());
        }
        
        parameterHoverLabel->setText(String(slider->getValue(), 3), false);
        
    }
    
    
    else if (slider == intensitySlider)
    {
        for (int i = 0; i < selectedPads.size(); i++)
        {
            int padNum = selectedPads[i];
            PAD_SETTINGS->setPadFxDistortionAtIntensity(intensitySlider->getValue());
        }
        
        parameterHoverLabel->setText(String(slider->getValue(), 3), false);
        
    }
    
    
    
}

void GuiDistortion::comboBoxChanged (ComboBox *comboBox)
{
    if (comboBox == alphaTouchMenu)
    {
        for (int i = 0; i < selectedPads.size(); i++)
        {
            int padNum = selectedPads[i];
            PAD_SETTINGS->setPadFxDistortionAlphaTouch(alphaTouchMenu->getSelectedId());
        }
        
    }
    
    else if (comboBox == shapeMenu)
    {
        for (int i = 0; i < selectedPads.size(); i++)
        {
            int padNum = selectedPads[i];
            PAD_SETTINGS->setPadFxDistortionShape(shapeMenu->getSelectedId());
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
            PAD_SETTINGS->setPadFxDistortionRate(lfoRate);
            PAD_SETTINGS->setPadFxDistortionRateMenu(rateMenu->getSelectedId());
        }
        
    }
    
}


void GuiDistortion::buttonClicked (Button *button)
{
    if (button == reverseButton)
    {
        for (int i = 0; i < selectedPads.size(); i++)
        {
            int padNum = selectedPads[i];
            PAD_SETTINGS->setPadFxDistortionAtReverse(reverseButton->getToggleState());
        }
        
    }
    
    else if (button == syncButton)
    {
        for (int i = 0; i < selectedPads.size(); i++)
        {
            int padNum = selectedPads[i];
            PAD_SETTINGS->setPadFxDistortionSync(syncButton->getToggleState());
        }
        
        rateSlider->setVisible(false);
        rateMenu->setVisible(false);
        
        if (syncButton->getToggleState() == 0) //off
            rateSlider->setVisible(true);
        else //on
            rateMenu->setVisible(true);
        
    }
}

void GuiDistortion::setCurrentlySelectedPad (Array<int> selectedPads_)
{
    selectedPads = selectedPads_;
}

void GuiDistortion::updateDisplay()
{
    //This method is used to set all the components to the currently selected pad's settings.
    rateSlider->setVisible(false);
    rateMenu->setVisible(false);
    
    //if an individual pad number is currently selected
    if(SINGLE_PAD)
    {
        int padNum = selectedPads[0];
        depthSlider->setValue(PAD_SETTINGS->getPadFxDistortionDepth(), false);
        rateSlider->setValue(PAD_SETTINGS->getPadFxDistortionRate(), false);
        rateMenu->setSelectedId(PAD_SETTINGS->getPadFxDistortionRateMenu(), true);
        syncButton->setToggleState(PAD_SETTINGS->getPadFxDistortionSync(), false);
        shapeMenu->setSelectedId(PAD_SETTINGS->getPadFxDistortionShape(), true);
        
        alphaTouchMenu->setSelectedId(PAD_SETTINGS->getPadFxDistortionAlphaTouch(), true);
        reverseButton->setToggleState(PAD_SETTINGS->getPadFxDistortionAtReverse(), false);
        intensitySlider->setValue(PAD_SETTINGS->getPadFxDistortionAtIntensity(), false);
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
void GuiDistortion::setTempo (float value)
{
    tempo = value;
    //OR
    tempo = AppSettings::Instance()->getGlobalTempo();
}

void GuiDistortion::mouseEnter (const MouseEvent &e)
{
    if (depthSlider->isMouseOver(true))
    {
        mainComponentRef.setInfoTextBoxText(translate("Depth/Mix Control. Sets the depth/mix of the LFO for the selected pads."));
        parameterHoverLabel->setText(String(depthSlider->getValue(), 3), false);
    }
    else if (rateSlider->isMouseOver(true))
    {
        mainComponentRef.setInfoTextBoxText(translate("LFO Rate Control. Sets the rate in Hz for the selected pads. If you would like to set the rate based on the tempo, click on the 'Sync' button."));
        parameterHoverLabel->setText(String(rateSlider->getValue(), 3), false);
    }
    else if (rateMenu->isMouseOver(true))
    {
        mainComponentRef.setInfoTextBoxText(translate("LFO Rate Menu. Sets the LFO rate for the selected pads. If you would like to set the rate in Hz, click on the 'Sync' button."));
    }
    else if (syncButton->isMouseOver(true))
    {
        mainComponentRef.setInfoTextBoxText(translate("Tempo Sync Button. Turn this button on to sync the LFO to the tempo, else you can set the LFO is Hz."));
    }
    else if (shapeMenu->isMouseOver(true))
    {
        mainComponentRef.setInfoTextBoxText(translate("Wave Shape Menu. Sets the LFO wave shape for the selected pads."));
    }
    else if (alphaTouchMenu->isMouseOver(true))
    {
        mainComponentRef.setInfoTextBoxText(translate(CommonInfoBoxText::alphaTouchMenu));
    }
    else if (reverseButton->isMouseOver(true))
    {
        mainComponentRef.setInfoTextBoxText(translate(CommonInfoBoxText::inverseButton));
    }
    else if (intensitySlider->isMouseOver(true))
    {
        mainComponentRef.setInfoTextBoxText(translate(CommonInfoBoxText::intensitySlider));
        parameterHoverLabel->setText(String(intensitySlider->getValue(), 3), false);
    }
    
}

void GuiDistortion::mouseExit (const MouseEvent &e)
{
    //remove any text
    mainComponentRef.setInfoTextBoxText (String::empty);
    parameterHoverLabel->setText(String::empty, false);
    
}
