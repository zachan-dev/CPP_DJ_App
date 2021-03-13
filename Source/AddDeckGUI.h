/*
  ==============================================================================

    AddDeckGUI.h
    Created: 7 Nov 2020 3:10:21pm
    Author:  chans

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class AddDeckGUI    : public Component
{
public:
    AddDeckGUI();
    ~AddDeckGUI();

    /**
    * Overrides default paint graphics function
    * @param  {Graphics&}
    * @return
    */
    void paint (Graphics&) override;
    /**
    * Overrides default window resized event handler function
    * @param
    * @return
    */
    void resized() override;
    
    friend class TracksManager;

private:
    TooltipWindow tooltipWindow;

    DrawablePath addPath;

    DrawableButton addTrackButton{ "CLICK TO ADD A TRACK", DrawableButton::ImageOnButtonBackgroundOriginalSize };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AddDeckGUI)
};
