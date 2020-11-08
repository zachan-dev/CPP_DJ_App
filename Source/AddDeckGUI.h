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

    void paint (Graphics&) override;
    void resized() override;
    
    friend class TracksManager;

private:
    TextButton addTrackButton{ "ADD A TRACK" };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AddDeckGUI)
};
