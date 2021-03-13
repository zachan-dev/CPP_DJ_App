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
    /**
    * Overrides default prepareToPlay function, to prepare the DJAudioPlayer to play
    * @param {int} samplesPerBlockExpected
    * @param {double} sampleRate
    * @return
    */
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    /**
    * Overrides default getNextAudioBlock function, to trigger the DJAudioPlayer's getNextAudioBlock function
    * @param {AudioSourceChannelInfo&} bufferToFill
    * @return
    */
    void getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill) override;
    /**
    * Overrides default releaseResources function, to trigger the DJAudioPlayer's releaseResources function
    * @param
    * @return
    */
    void releaseResources() override;

    /**
    * Resets the track to its initial state
    * @param
    * @return
    */
    void reset();

private:
    DJAudioPlayer player;
    DeckGUI deckGUI;
    int trackID;

    friend class TracksManager;
    friend class PlaylistComponent;
};
