/*
  ==============================================================================

    WaveformDisplay.h
    Created: 5 Nov 2020 4:38:13pm
    Author:  chans

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class WaveformDisplay    : public Component,
                           public ChangeListener
{
public:
    WaveformDisplay(AudioFormatManager& formatManagerToUse,
                    AudioThumbnailCache& cacheToUse);
    ~WaveformDisplay();
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

    //Implement ChangeListener
    //==============================================
    /**
    * Overrides default waveform change listener callback function
    * @param {ChangeBroadcaster*} source : change broadcaster source
    * @return
    */
    void changeListenerCallback(ChangeBroadcaster* source) override;

    /**
    * Load audio file to the waveform display using file path
    * @param {URL} audioURL : audio file URL
    * @return
    */
    void loadURL(URL audioURL);
    /**
    * Set relative position of the waveform display
    * @param {double} pos : between 0=start and 1=end
    * @return
    */
    void setPositionRelative(double pos);
    /**
    * Reset the waveform display to its initial state
    * @param
    * @return
    */
    void reset();

private:
    AudioThumbnail audioThumb;
    bool fileLoaded;
    double position;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveformDisplay)
};
