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
#include <algorithm>
#include <string>
#include <fstream>

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
    PlaylistComponent(TracksManager* tm, TextEditor* te);
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
    void deleteKeyPressed(int lastRowSelected) override;
    void sortOrderChanged(int newSortColumnId, bool isForwards) override;

    //Implement Button::Listener
    //==============================================
    void buttonClicked(Button* button) override;

    bool pushFileToPlaylist(File* file);
    static double getAudioFileDuration(File* file, AudioFormatManager* fm);
    static String toUniversalURL(String path);
    void refresh(bool deleteNonExistingFiles = true);
    bool isFileOnList(File* file);
    bool readFromFile(File* file);
    bool writeToFile(File* file);
    void saveToTempFile(bool notificationOn = true);
    void loadFromTempFile();
    void sort(String sortBy, bool asending);

    static const String TEMP_FILENAME;
    static const String TEMP_FILEEXT;

private:

    TracksManager* tracksManager;
    TextEditor* searchTextbox;

    TableListBox tableComponent;
    std::vector<File*> trackFiles;
    std::vector<File*> searchResults;

    int columnsNum = 4;

    friend class MusicLibrary;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlaylistComponent)
};
