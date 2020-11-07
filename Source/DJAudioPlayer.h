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
        void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
        void getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill) override;
        void releaseResources() override;

        void loadURL(URL audioURL);
        void setGain(double gain);
        void setSpeed(double ratio);
        void setPosition(double posInSecs);
        void setPositionRelative(double pos);

        void start();
        void stop();

        /* get the relative position of the playhead */
        double getPositionRelative() const;

    private:
        // Audio Playback Onion layers
        AudioFormatManager& formatManager; // audio file uncompressor
        std::unique_ptr<AudioFormatReaderSource> readerSource; // smart pointer to read the audio file from the AudioFormatManager
        AudioTransportSource transportSource; // add a layer for volume control / startOrStop control
        ResamplingAudioSource resampleSource{ &transportSource, false, 2 }; // add a layer for speed control
};