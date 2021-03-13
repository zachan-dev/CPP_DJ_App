/*
  ==============================================================================

    DJAudioPlayer.h
    Created: 5 Nov 2020 11:01:43am
    Author:  chans

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class DJAudioPlayer : public AudioSource {
    public:
        DJAudioPlayer(AudioFormatManager& _formatManager);
        ~DJAudioPlayer();

        //==============================================================================
        /**
        * Overrides default prepareToPlay function, to prepare transportSource and resampleSource to play
        * @param {int} samplesPerBlockExpected
        * @param {double} sampleRate
        * @return
        */
        void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
        /**
        * Overrides default getNextAudioBlock function, to trigger resampleSource's getNextAudioBlock function
        * @param {AudioSourceChannelInfo&} bufferToFill
        * @return
        */
        void getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill) override;
        /**
        * Overrides default releaseResources function, to release resources on deletion
        * @param
        * @return
        */
        void releaseResources() override;

        /**
        * Read from file path and load the audio file to the player
        * @param {URL} audioURL : url to the input audio file
        * @return
        */
        bool loadURL(URL audioURL);
        /**
        * Set player's volume relative gain
        * @param {double} gain : volume relative gain between 0 (silence) and 1 (greatest gain)
        * @return
        */
        void setGain(double gain);
        /**
        * Set player's speed multipler
        * @param {double} ratio : speed multipler, 1=normal, <1=slowerThanNormal, >1=fasterThanNormal
        * @return
        */
        void setSpeed(double ratio);
        /**
        * Set player's playback position
        * @param {double} posInSecs : playback position in seconds
        * @return
        */
        void setPosition(double posInSecs);
        /**
        * Set player's playback relative position
        * @param {double} posInSecs : playback relative position, between 0 (start) and 1 (end)
        * @return
        */
        void setPositionRelative(double pos);

        /**
        * Start the audio player
        * @param
        * @return
        */
        void start();
        /**
        * Stop the audio player
        * @param
        * @return
        */
        void stop();

        /* get the relative position of the playhead */
        /**
        * Get the relative position of the playhead
        * @param
        * @return {double} : relative position of the playhead, between 0 (start) and 1 (end)
        */
        double getPositionRelative() const;

        /**
        * Reset the audio player to initial state
        * @param
        * @return
        */
        void reset();

    private:
        // Audio Playback Onion layers
        AudioFormatManager& formatManager; // audio file uncompressor
        std::unique_ptr<AudioFormatReaderSource> readerSource; // smart pointer to read the audio file from the AudioFormatManager
        AudioTransportSource transportSource; // add a layer for volume control / startOrStop control
        ResamplingAudioSource resampleSource{ &transportSource, false, 2 }; // add a layer for speed control

        friend class DeckGUI;
};