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

    void paint (Graphics&) override;
    void resized() override;

    // implement Button::Listener
    //==============================================================================
    void buttonClicked(Button* button) override;

    // implement Slider::Listener
    //==============================================================================
    void sliderValueChanged(Slider* slider) override;

    // implement FileDragAndDropTarget
    //==============================================================================
    bool isInterestedInFileDrag(const StringArray& files) override;
    void filesDropped(const StringArray& files, int x, int y) override;

    // implement Timer
    //==============================================================================
    void timerCallback() override;

    void reset();
    bool loadURL(URL& fileURL);

private:
    TextButton closeButton{ "X" };
    TextButton playButton{ "PLAY" };
    TextButton pauseButton{ "PAUSE" };
    TextButton stopButton{ "STOP" };
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