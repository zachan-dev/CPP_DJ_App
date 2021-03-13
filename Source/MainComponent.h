/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PlaylistComponent.h"
#include "Track.h"
#include "AddDeckGUI.h"
#include <vector>
#include "TracksManager.h"
#include "MusicLibrary.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent   : public AudioAppComponent
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent();

    //==============================================================================
    /**
    * Overrides default prepareToPlay function, to prepare tracksManager to play
    * @param {int} samplesPerBlockExpected
    * @param {double} sampleRate
    * @return
    */
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    /**
    * Overrides default getNextAudioBlock function, to trigger tracksManager's getNextAudioBlock function
    * @param {AudioSourceChannelInfo&} bufferToFill
    * @return
    */
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override;
    /**
    * Overrides default releaseResources function, to release resources on deletion
    * @param
    * @return
    */
    void releaseResources() override;

    //==============================================================================
    /**
    * Overrides default paint graphics function
    * @param  {Graphics&}
    * @return
    */
    void paint (Graphics& g) override;
    /**
    * Overrides default window resized event handler function
    * @param
    * @return
    */
    void resized() override;

    /**
    * Show welcome message on startup
    * @param
    * @return
    */
    void showWelcomeMessageBox();

private:
    //==============================================================================
    // Your private member variables go here...

    TracksManager tracksManager;
    MusicLibrary musicLibrary{ &tracksManager };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
