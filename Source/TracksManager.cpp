/*
  ==============================================================================

    TracksManager.cpp
    Created: 8 Nov 2020 11:35:56am
    Author:  chans

  ==============================================================================
*/

#include <JuceHeader.h>
#include "TracksManager.h"

//==============================================================================
TracksManager::TracksManager()
    : tracks{ initTracks() }
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

    for (auto& track : tracks) {
        addAndMakeVisible(track->deckGUI);
        track->deckGUI.setVisible(false);
        track->deckGUI.closeButton.addListener(this);
    }
    addAndMakeVisible(addDeck);

    addDeck.addTrackButton.addListener(this);

    formatManager.registerBasicFormats(); // tell fm know about the allowed formats
}

TracksManager::~TracksManager()
{
    for (auto& track : tracks) {
        delete track;
    }
}

//==============================================================================
void TracksManager::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    mixerSource.prepareToPlay(
        samplesPerBlockExpected,
        sampleRate
    );

    for (auto& track : tracks) {
        track->prepareToPlay(
            samplesPerBlockExpected,
            sampleRate
        );
        mixerSource.addInputSource(&track->player, false);
    }
}
void TracksManager::getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill)
{
    mixerSource.getNextAudioBlock(bufferToFill);
}
void TracksManager::releaseResources()
{
    for (auto& track : tracks) {
        track->releaseResources();
    }

    mixerSource.releaseResources();
}

//==============================================================================
void TracksManager::paint (Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (Colours::white);
    g.setFont (14.0f);
    g.drawText ("TracksManager", getLocalBounds(),
                Justification::centred, true);   // draw some placeholder text
}

void TracksManager::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    std::vector<Track*> VTs = visibleTracks();
    if (VTs.size() > 0) {
        int deckHeight = getHeight();
        int deckWidth = (VTs.size() == tracks.size()) ? getWidth() / VTs.size() : getWidth() / (VTs.size() + 1);
        for (int i = 0; i < VTs.size(); ++i) {
            VTs[i]->deckGUI.setBounds(i * deckWidth, 0, deckWidth, deckHeight);
        }
        if (VTs.size() != tracks.size()) {
            addDeck.setVisible(true);
            addDeck.setBounds(VTs.size() * deckWidth, 0, deckWidth, deckHeight);
        }
        else addDeck.setVisible(false);
    }
    else {
        addDeck.setBounds(0, 0, getWidth(), getHeight());
    }
}

// Implement Button::Listener
//==============================================================================
void TracksManager::buttonClicked(Button* button)
{
    if (button == &(addDeck.addTrackButton)) {
        addTrack();
    }
    for (auto& track : tracks) {
        if (button == &(track->deckGUI.closeButton)) {
            hideTrack(track);
        }
    }
}


std::vector<Track*> TracksManager::initTracks()
{
    std::vector<Track*> rtn;
    for (int i = 0; i < TRACKS_LIMIT; ++i) {
        rtn.push_back(new Track(formatManager, thumbCache));
    }
    return rtn;
}
void TracksManager::addTrack()
{
    for (auto& track : tracks) {
        if (!track->deckGUI.isVisible()) {
            track->deckGUI.setVisible(true);
            break;
        }
    }
    resized();
}
void TracksManager::hideTrack(Track* track)
{
    track->deckGUI.setVisible(false);
    //reset track TODO
    track->reset();
    resized();
}
std::vector<Track*> TracksManager::visibleTracks()
{
    std::vector<Track*> rtn;
    for (auto& track : tracks) {
        if (track->deckGUI.isVisible()) {
            rtn.push_back(track);
        }
    }
    return rtn;
}
