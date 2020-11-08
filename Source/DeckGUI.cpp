/*
  ==============================================================================

    DeckGUI.cpp
    Created: 5 Nov 2020 2:27:03pm
    Author:  chans

  ==============================================================================
*/

#include <JuceHeader.h>
#include "DeckGUI.h"

//==============================================================================
DeckGUI::DeckGUI(DJAudioPlayer* _player,
                AudioFormatManager& formatManagerToUse,
                AudioThumbnailCache& cacheToUse)
    : player{ _player }, 
      waveformDisplay{ formatManagerToUse, cacheToUse }
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

    addAndMakeVisible(closeButton);
    addAndMakeVisible(playButton);
    addAndMakeVisible(stopButton);
    addAndMakeVisible(loadButton);
    addAndMakeVisible(volSlider);
    addAndMakeVisible(speedSlider);
    addAndMakeVisible(posSlider);
    addAndMakeVisible(waveformDisplay);

    // register listeners
    //closeButton listener is in Main
    playButton.addListener(this);
    stopButton.addListener(this);
    loadButton.addListener(this);
    volSlider.addListener(this);
    speedSlider.addListener(this);
    posSlider.addListener(this);

    volSlider.setRange(0.0, 1.0); // set volume range limit
    posSlider.setRange(0.0, 1.0);

    volSlider.setValue(1.0);
    speedSlider.setValue(1.0);

    startTimer(500); // every 500 ms
}

DeckGUI::~DeckGUI()
{
    stopTimer();
}

void DeckGUI::paint (Graphics& g)
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
    g.drawText ("DeckGUI", getLocalBounds(),
                Justification::centred, true);   // draw some placeholder text
}

void DeckGUI::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

    double rowH = getHeight() / 9;

    closeButton.setBounds(0, 0, getWidth(), rowH);
    playButton.setBounds(0, rowH, getWidth(), rowH);
    stopButton.setBounds(0, rowH * 2, getWidth(), rowH);

    volSlider.setBounds(0, rowH * 3, getWidth(), rowH);
    speedSlider.setBounds(0, rowH * 4, getWidth(), rowH);
    posSlider.setBounds(0, rowH * 5, getWidth(), rowH);

    waveformDisplay.setBounds(0, rowH * 6, getWidth(), rowH * 2);

    loadButton.setBounds(0, rowH * 8, getWidth(), rowH);
}

// implement Button::Listener
//==============================================================================
void DeckGUI::buttonClicked(Button* button) {
    if (button == &playButton) {
        DBG("DeckGUI::buttonClicked Play button was clicked");
        player->start();
    }
    if (button == &stopButton) {
        DBG("DeckGUI::buttonClicked Stop button was clicked");
        player->stop();
    }
    if (button == &loadButton) {
        DBG("DeckGUI::buttonClicked Load button was clicked");

        FileChooser chooser{ "Select a file..." };
        if (chooser.browseForFileToOpen()) // will return true if user choose >= 1 files
        {
            player->loadURL(URL{ chooser.getResult() });
            waveformDisplay.loadURL(URL{ chooser.getResult() });
        }
    }
}

// implement Slider::Listener
//==============================================================================
void DeckGUI::sliderValueChanged(Slider* slider) {
    if (slider == &volSlider) {
        player->setGain(slider->getValue());
    }
    if (slider == &speedSlider) {
        player->setSpeed(slider->getValue());
    }
    if (slider == &posSlider) {
        player->setPositionRelative(slider->getValue());
    }
}

// implement FileDragAndDropTarget
//==============================================================================
bool DeckGUI::isInterestedInFileDrag(const StringArray& files) {
    DBG("DeckGUI::isInterestedInFileDrag");
    return true; // interested in all kinds of files
}
void DeckGUI::filesDropped(const StringArray& files, int x, int y) {
    DBG("DeckGUI::filesDropped");
    if (files.size() == 1)
    {
        player->loadURL(URL{ File{files[0]} });
        waveformDisplay.loadURL(URL{ File{files[0]} });
    }
}

// implement Timer
//==============================================================================
void DeckGUI::timerCallback() {
    //DBG("DeckGUI::timerCallback");
    waveformDisplay.setPositionRelative(player->getPositionRelative());
}

void DeckGUI::reset() {
    player->stop();
    volSlider.setValue(1.0);
    speedSlider.setValue(1.0);
    posSlider.setValue(1.0);
    posSlider.setValue(0.0);
    waveformDisplay.reset();
}