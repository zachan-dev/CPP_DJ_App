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

    // for Close Track Alert Box
    static void closeTrackAlertBoxResultChosen(int result, TracksManager* tm);

    std::vector<Track*> initTracks();
    void addTrack();
    void hideTrack(Track* track);
    std::vector<Track*> visibleTracks();
    Track* getTrackUsingID(int id);
    StringArray getAvaliableTrackNumbers();

private:
    const static int TRACKS_LIMIT = 5;

    AudioFormatManager formatManager;
    AudioThumbnailCache thumbCache{ 100 };

    std::vector<Track*> tracks;
    Track* trackToBeClosed; // for close track alert box use
    AddDeckGUI addDeck;

    MixerAudioSource mixerSource;

    friend class PlaylistComponent;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TracksManager)
};
