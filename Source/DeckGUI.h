/*
  ==============================================================================

    DeckGUI.h
    Created: 5 Nov 2020 2:27:03pm
    Author:  chans

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h"
#include "WaveformDisplay.h"
#include "OtherLookAndFeel.h"

//==============================================================================
/*
*/
class DeckGUI : public Component,
                public Button::Listener,
                public Slider::Listener,
                public FileDragAndDropTarget,
                public Timer
{
public:
    DeckGUI(DJAudioPlayer* player,
            AudioFormatManager& formatManagerToUse, 
            AudioThumbnailCache& cacheToUse,
            int trackID);
    ~DeckGUI();

    /**
    * Overrides default paint graphics function
    * @param  {Graphics&}
    * @return
    */
    void paint (Graphics&) override;
    /**
    * Overrides default window resized event handler function
    * @param
    * @return
    */
    void resized() override;

    // implement Button::Listener
    //==============================================================================
    /**
    * Overrides default button onclick event handler function
    * @param  {Button*} button
    * @return
    */
    void buttonClicked(Button* button) override;

    // implement Slider::Listener
    //==============================================================================
    /**
    * Overrides default slider valueChanged event handler function
    * @param  {Slider*} slider
    * @return
    */
    void sliderValueChanged(Slider* slider) override;

    // implement FileDragAndDropTarget
    //==============================================================================
    /**
    * Overrides default file draggedTo event trigger function
    * @param  {StringArray&} files : files being mouse dragged
    * @return {bool} : whether filesDropped event handler should be triggered by the input files
    */
    bool isInterestedInFileDrag(const StringArray& files) override;
    /**
    * Overrides default files dropped event handler function
    * @param  {StringArray*} files : interested files dropped
    * @param  {int} x : drop location's x coordinate
    * @param {int} y : drop location's y coordinate
    * @return
    */
    void filesDropped(const StringArray& files, int x, int y) override;

    // implement Timer
    //==============================================================================
    /**
    * Overrides default timer callback function to synchronise waveform display with the audio playback 
    * @param
    * @return
    */
    void timerCallback() override;

    /**
    * Resets all GUI components to their initial states
    * @param
    * @return
    */
    void reset();
    /**
    * Resets all GUI components to their initial states
    * @param {URL&} fileURL : file path to be loaded into the deck
    * @return {bool} : is file loading to waveform and audio player successful
    */
    bool loadURL(URL& fileURL);

private:
    TooltipWindow tooltipWindow;

    DrawablePath closePath;
    DrawablePath playPath;
    DrawablePath pausePath;
    DrawablePath stopPath;

    DrawableButton closeButton{ "CLOSE", DrawableButton::ImageOnButtonBackground };
    DrawableButton playButton{ "PLAY", DrawableButton::ImageOnButtonBackground };
    DrawableButton pauseButton{ "PAUSE", DrawableButton::ImageOnButtonBackground };
    DrawableButton stopButton{ "STOP", DrawableButton::ImageOnButtonBackground };
    ToggleButton loopButton{ "LOOP" };

    Slider volSlider;
    Label volLabel;
    Slider speedSlider;
    Label speedLabel;
    Slider posSlider;
    Label posLabel;
    OtherLookAndFeel volSliderLookAndFeel;
    OtherLookAndFeel speedSliderLookAndFeel;
    OtherLookAndFeel posSliderLookAndFeel;

    WaveformDisplay waveformDisplay;

    DJAudioPlayer* player;

    int trackID;

    friend class TracksManager;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DeckGUI)
};