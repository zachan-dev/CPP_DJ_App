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

    void paint (Graphics&) override;
    void resized() override;

    // Implement ChangeListener
    void changeListenerCallback(ChangeBroadcaster* source) override;

    void loadURL(URL audioURL);

    void setPositionRelative(double pos);

    void reset();

private:
    AudioThumbnail audioThumb;
    bool fileLoaded;
    double position;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveformDisplay)
};
