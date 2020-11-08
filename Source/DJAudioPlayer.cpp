/*
  ==============================================================================

    DJAudioPlayer.cpp
    Created: 5 Nov 2020 11:01:43am
    Author:  chans

  ==============================================================================
*/

#include "DJAudioPlayer.h"

DJAudioPlayer::DJAudioPlayer(AudioFormatManager& _formatManager)
    :formatManager(_formatManager)
{

}
DJAudioPlayer::~DJAudioPlayer() {

}

//==============================================================================
void DJAudioPlayer::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    // play function wrapped in load button click listener

    transportSource.prepareToPlay(
        samplesPerBlockExpected,
        sampleRate
    );
    resampleSource.prepareToPlay(
        samplesPerBlockExpected,
        sampleRate
    );
}
void DJAudioPlayer::getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill)
{
    resampleSource.getNextAudioBlock(bufferToFill);
}
void DJAudioPlayer::releaseResources()
{
    resampleSource.releaseResources();
}

bool DJAudioPlayer::loadURL(URL audioURL) {
    auto* reader = formatManager.createReaderFor(audioURL.createInputStream(false));
    if (reader != nullptr) // good file
    {
        std::unique_ptr<AudioFormatReaderSource> newSource(new AudioFormatReaderSource(reader, true));
        transportSource.setSource(newSource.get(), 0, nullptr, reader->sampleRate);
        readerSource.reset(newSource.release());
        //transportSource.start(); // wrapped in start function
        return true;
    }
    else
    {
        DBG("Something went wrong loading the file ");
        return false;
    }
}
void DJAudioPlayer::setGain(double gain) {
    if (gain < 0 || gain > 1.0) {
        DBG("DJAudioPlayer::setGain gain should be between 0 and 1");
    }
    else {
        transportSource.setGain(gain);
    }
}
void DJAudioPlayer::setSpeed(double ratio) {
    if (ratio < 0 || ratio > 100.0) {
        DBG("DJAudioPlayer::setSpeed ratio should be between 0 and 100");
    }
    else {
        resampleSource.setResamplingRatio(ratio);
    }
}
void DJAudioPlayer::setPosition(double posInSecs) {
    transportSource.setPosition(posInSecs);
}

void DJAudioPlayer::setPositionRelative(double pos) {
    if (pos < 0 || pos > 1.0) {
        DBG("DJAudioPlayer::setPositionRelative pos should be between 0 and 1");
    }
    else {
        double posInSecs = pos * transportSource.getLengthInSeconds();
        setPosition(posInSecs);
    }
}

void DJAudioPlayer::start() {
    transportSource.start();
}
void DJAudioPlayer::stop() {
    transportSource.stop();
}

double DJAudioPlayer::getPositionRelative() const {
    if (transportSource.getLengthInSeconds() == 0) return 0.0;
    return transportSource.getCurrentPosition() / transportSource.getLengthInSeconds();
}

void DJAudioPlayer::reset() {
    transportSource.setSource(nullptr);
}