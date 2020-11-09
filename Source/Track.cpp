/*
  ==============================================================================

    Track.cpp
    Created: 7 Nov 2020 12:22:19pm
    Author:  chans

  ==============================================================================
*/

#include "Track.h"

//==============================================================================
Track::Track(AudioFormatManager& fm, AudioThumbnailCache& tc, int trackID) 
    : player{ fm }, 
      deckGUI{ &player, fm, tc, trackID },
      trackID{ trackID }
{

}
Track::~Track() 
{

}

//==============================================================================
void Track::prepareToPlay(int samplesPerBlockExpected, double sampleRate) {
    player.prepareToPlay(
        samplesPerBlockExpected,
        sampleRate
    );
}
void Track::getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill) {

}
void Track::releaseResources() {
    player.releaseResources();
}

void Track::reset() {
    // reset deckGUI
    player.reset();
    deckGUI.reset();
}