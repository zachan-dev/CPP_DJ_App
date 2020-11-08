/*
  ==============================================================================

    OtherLookAndFeel.cpp
    Created: 8 Nov 2020 1:53:15pm
    Author:  chans

  ==============================================================================
*/

#include "OtherLookAndFeel.h"

OtherLookAndFeel::OtherLookAndFeel(Colour rotarySliderOutlineColour, Colour rotarySliderFillColour, Colour thumbColour)
{
    setColour(Slider::rotarySliderOutlineColourId, rotarySliderOutlineColour);
    setColour(Slider::rotarySliderFillColourId, rotarySliderFillColour);
    setColour(Slider::thumbColourId, thumbColour);
}