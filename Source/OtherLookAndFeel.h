/*
  ==============================================================================

    OtherLookAndFeel.h
    Created: 8 Nov 2020 1:53:15pm
    Author:  chans

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class OtherLookAndFeel : public LookAndFeel_V4
{
public:
    /**
    * Constructor: LookAndFeel for sliders in DeckGUI
    * @param
    * @return
    */
    OtherLookAndFeel(Colour rotarySliderOutlineColour, Colour rotarySliderFillColour, Colour thumbColour);
};