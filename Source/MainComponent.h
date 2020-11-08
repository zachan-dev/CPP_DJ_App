/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h"
#include "DeckGUI.h"
#include "PlaylistComponent.h"
#include "Track.h"
#include "AddDeckGUI.h"
#include <vector>

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent   : public AudioAppComponent,
                        public Button::Listener
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent();

    //==============================================================================
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    //==============================================================================
    void paint (Graphics& g) override;
    void resized() override;

    // Implement Button::Listener
    //==============================================================================
    void buttonClicked(Button* button) override;

    const static int TRACKS_LIMIT = 3;
    std::vector<Track*> initTracks();
    void addTrack();
    void hideTrack(Track* track);
    std::vector<Track*> visibleTracks();

private:
    //==============================================================================
    // Your private member variables go here...

    AudioFormatManager formatManager;
    AudioThumbnailCache thumbCache{ 100 };

    std::vector<Track*> tracks;
    AddDeckGUI addDeck;

    MixerAudioSource mixerSource;

    PlaylistComponent playlistComponent;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
