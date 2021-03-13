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
    /**
    * Overrides default prepareToPlay function, to add tracks to the audio mixer, and prepare the mixer and the tracks to play
    * @param {int} samplesPerBlockExpected
    * @param {double} sampleRate
    * @return
    */
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    /**
    * Overrides default getNextAudioBlock function, to trigger the mixer's getNextAudioBlock function
    * @param {AudioSourceChannelInfo&} bufferToFill
    * @return
    */
    void getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill) override;
    /**
    * Overrides default releaseResources function, to trigger the mixer's releaseResources function
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
    void paint(Graphics& g) override;
    /**
    * Overrides default window resized event handler function
    * @param
    * @return
    */
    void resized() override;

    // Implement Button::Listener
    //==============================================================================
    /**
    * Overrides default buttonClicked event handler
    * @param {Button*} button
    * @return
    */
    void buttonClicked(Button* button) override;

    // for Close Track Alert Box
    /**
    * Get the chosen result (close track or cancel) for the alert box when closing the selected track
    * @param {int} result : close the track or not (1=True, 0=False)
    * @param {TracksManager*} tm
    * @return
    */
    static void closeTrackAlertBoxResultChosen(int result, TracksManager* tm);

    /**
    * Initialise all the tracks
    * @param
    * @return {vector<Track*>} : vector of initialised tracks
    */
    std::vector<Track*> initTracks();
    /**
    * Show a hidden track
    * @param
    * @return
    */
    void addTrack();
    /**
    * Hide the selected track
    * @param {Track*} track
    * @return
    */
    void hideTrack(Track* track);
    /**
    * Return vector of all visible tracks
    * @param
    * @return {vector<Track*>} : vector of all visible tracks
    */
    std::vector<Track*> visibleTracks();
    /**
    * Get the track using its ID
    * @param {int} id : track ID
    * @return {Track*} : the found track or not found(nullptr)
    */
    Track* getTrackUsingID(int id);
    /**
    * Return array of all visible tracks' IDs
    * @param
    * @return {StringArray} : array of all visible tracks' IDs
    */
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
