/*
  ==============================================================================

    AddDeckGUI.cpp
    Created: 7 Nov 2020 3:10:21pm
    Author:  chans

  ==============================================================================
*/

#include <JuceHeader.h>
#include "AddDeckGUI.h"

//==============================================================================
AddDeckGUI::AddDeckGUI()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    addAndMakeVisible(addTrackButton);
}

AddDeckGUI::~AddDeckGUI()
{
}

void AddDeckGUI::paint (Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (Colours::white);
    g.setFont (14.0f);
    g.drawText ("AddDeckGUI", getLocalBounds(),
                Justification::centred, true);   // draw some placeholder text
}

void AddDeckGUI::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    addTrackButton.setBounds(0, 0, getWidth(), getHeight());
}