/*
  ==============================================================================

    PlaylistComponent.h
    Created: 6 Nov 2020 1:48:10am
    Author:  chans

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <vector>
#include <string>

#include "TracksManager.h"
#include "DJAudioPlayer.h"

//==============================================================================
/*
*/
class PlaylistComponent    : public Component,
                             public TableListBoxModel,
                             public Button::Listener
{
public:
    PlaylistComponent(TracksManager* tm);
    ~PlaylistComponent();

    void paint (Graphics&) override;
    void resized() override;

    //Implement TableListBoxModel
    //==============================================
    int getNumRows() override;
    void paintRowBackground(Graphics& g,
                        int rowNumber,
                        int width,
                        int height,
                        bool rowIsSelected) override;
    void paintCell(Graphics& g, 
                int rowNumber, 
                int columnId, 
                int width, 
                int height, 
                bool rowIsSelected) override;
    Component* refreshComponentForCell(int rowNumber,
                            int columnId,
                            bool isRowSelected,
                            Component* existingComponentToUpdate) override;

    //Implement Button::Listener
    //==============================================
    void buttonClicked(Button* button) override;

    bool pushFileToPlaylist(File* file);
    static double getAudioFileDuration(File* file, AudioFormatManager* fm);
    static String toUniversalURL(String path);
    void refresh();

private:

    TracksManager* tracksManager;

    TableListBox tableComponent;
    std::vector<File*> trackFiles;

    int columnsNum = 4;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlaylistComponent)
};
