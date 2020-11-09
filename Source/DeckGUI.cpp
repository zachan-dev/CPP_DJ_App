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
                AudioThumbnailCache& cacheToUse,
                int trackID)
    : player{ _player }, 
      waveformDisplay{ formatManagerToUse, cacheToUse },
      volSliderLookAndFeel{
        Colour(189, 8, 28), // Pinterest red
        Colours::red, // Youtube red
        Colours::black // Youtube black
      },
      speedSliderLookAndFeel{
        Colour(18, 140, 126), // Whatsapp green
        Colour(37, 211, 102), // Whatsapp light-green
        Colour(7, 94, 84) // Whatsapp dark-green
      },
      posSliderLookAndFeel{
        Colour(0, 119, 181), // LinkedIn blue
        Colour(29, 161, 242), // Twitter blue
        Colour(20, 23, 26) // Twitter black
      },
      trackID{ trackID }
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

    addAndMakeVisible(closeButton);
    addAndMakeVisible(playButton);
    addAndMakeVisible(pauseButton);
    addAndMakeVisible(stopButton);
    addAndMakeVisible(loopButton);
    addAndMakeVisible(volSlider);
    addAndMakeVisible(volLabel);
    addAndMakeVisible(speedSlider);
    addAndMakeVisible(speedLabel);
    addAndMakeVisible(posSlider);
    addAndMakeVisible(posLabel);
    addAndMakeVisible(waveformDisplay);

    // customise sliders
    volSlider.setSliderStyle(Slider::SliderStyle::Rotary);
    speedSlider.setSliderStyle(Slider::SliderStyle::Rotary);
    posSlider.setSliderStyle(Slider::SliderStyle::Rotary);
    volSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 100, 25);
    speedSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 100, 25);
    posSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 100, 25);
    volLabel.setText("Volume", dontSendNotification);
    speedLabel.setText("Speed", dontSendNotification);
    posLabel.setText("Position", dontSendNotification);
    volLabel.setJustificationType(Justification::centred);
    speedLabel.setJustificationType(Justification::centred);
    posLabel.setJustificationType(Justification::centred);
    volLabel.attachToComponent(&volSlider, false);
    speedLabel.attachToComponent(&speedSlider, false);
    posLabel.attachToComponent(&posSlider, false);
    volSlider.setLookAndFeel(&volSliderLookAndFeel);
    speedSlider.setLookAndFeel(&speedSliderLookAndFeel);
    posSlider.setLookAndFeel(&posSliderLookAndFeel);

    // register listeners
    //closeButton listener is in Main
    playButton.addListener(this);
    pauseButton.addListener(this);
    stopButton.addListener(this);
    loopButton.addListener(this);
    volSlider.addListener(this);
    speedSlider.addListener(this);
    posSlider.addListener(this);

    playButton.setColour(TextButton::ColourIds::buttonColourId, Colour(37, 211, 102)); // green
    pauseButton.setColour(TextButton::ColourIds::buttonColourId, Colour(255, 87, 0)); // orange
    stopButton.setColour(TextButton::ColourIds::buttonColourId, Colour(205, 32, 31)); // red
    closeButton.setColour(TextButton::ColourIds::buttonColourId, Colours::red); // red

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

    // Show which track it is
    g.drawText ("Track #" + std::to_string(trackID), getLocalBounds(),
                Justification::centredBottom, true);   
}

void DeckGUI::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

    double rowH = getHeight() / 8;
    double rotaryH = 3 * rowH;
    double rotaryW = getWidth() / 3;
    double controlsW = getWidth() / 4;

    playButton.setBounds(0, 0, controlsW, rowH);
    pauseButton.setBounds(controlsW, 0, controlsW, rowH);
    stopButton.setBounds(2 * controlsW, 0 * 3, controlsW, rowH);
    closeButton.setBounds(3 * controlsW, 0, controlsW, rowH);

    volSlider.setBounds(0, rowH * 2, rotaryW, rotaryH);
    speedSlider.setBounds(rotaryW, rowH * 2, rotaryW, rotaryH);
    posSlider.setBounds(2 * rotaryW, rowH * 2, rotaryW, rotaryH);

    waveformDisplay.setBounds(0, rowH * 5, getWidth(), rowH * 2);

    loopButton.setBounds(0, rowH * 7, getWidth(), rowH);
}

// implement Button::Listener
//==============================================================================
void DeckGUI::buttonClicked(Button* button) {
    // close Button handler in TracksManager
    if (button == &playButton) {
        DBG("DeckGUI::buttonClicked Play button was clicked");
        player->start();
    }
    if (button == &pauseButton) {
        DBG("DeckGUI::buttonClicked Pause button was clicked");
        player->stop();
    }
    if (button == &stopButton) {
        DBG("DeckGUI::buttonClicked Stop button was clicked");
        player->stop();
        posSlider.setValue(1.0);
        posSlider.setValue(0.0);
    }
    //if (button == &loadButton) {
    //    DBG("DeckGUI::buttonClicked Load button was clicked");

    //    FileChooser chooser{ "Select a file..." };
    //    if (chooser.browseForFileToOpen()) // will return true if user choose >= 1 files
    //    {
    //        loadURL(URL{ chooser.getResult() });
    //    }
    //}
    if (button == &loopButton) {
        if (player->readerSource != nullptr) {
            // set looping on AudioFormatReaderSource
            player->readerSource->setLooping(loopButton.getToggleStateValue() == 1);
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
    loopButton.setToggleState(false, NotificationType::dontSendNotification);
}

bool DeckGUI::loadURL(URL& fileURL)
{
    bool sucessLoading = player->loadURL(fileURL);
    if (sucessLoading) {
        reset();
        waveformDisplay.loadURL(fileURL);
        player->readerSource->setLooping(loopButton.getToggleStateValue() == 1); // set looping on AudioFormatReaderSource
        return true;
    }
    return false;
}