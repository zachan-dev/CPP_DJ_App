/*
  ==============================================================================

    TracksManager.h
    Created: 8 Nov 2020 11:35:56am
    Author:  chans

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <vector>
#include "DeckGUI.h"
#include "Track.h"
#include "AddDeckGUI.h"

//==============================================================================
/*
*/
class TracksManager    : public AudioAppComponent,
                         public Button::Listener
{
public:
    TracksManager();
    ~TracksManager();

    //==============================================================================
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    //==============================================================================
    void paint(Graphics& g) override;
    void resized() override;

    // Implement Button::Listener
    //==============================================================================
    void buttonClicked(Button* button) override;

    std::vector<Track*> initTracks();
    void addTrack();
    void hideTrack(Track* track);
    std::vector<Track*> visibleTracks();

private:
    const static int TRACKS_LIMIT = 3;

    AudioFormatManager formatManager;
    AudioThumbnailCache thumbCache{ 100 };

    std::vector<Track*> tracks;
    AddDeckGUI addDeck;

    MixerAudioSource mixerSource;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TracksManager)
};
