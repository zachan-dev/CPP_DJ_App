/*
  ==============================================================================

    Track.h
    Created: 7 Nov 2020 12:22:19pm
    Author:  chans

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h"
#include "DeckGUI.h"

class Track : public AudioAppComponent {

public:
    //==============================================================================
    Track(AudioFormatManager& fm, AudioThumbnailCache& tc, int trackID);
    ~Track();

    //==============================================================================
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    void reset();

private:
    DJAudioPlayer player;
    DeckGUI deckGUI;
    int trackID;

    friend class TracksManager;
    friend class PlaylistComponent;
};
