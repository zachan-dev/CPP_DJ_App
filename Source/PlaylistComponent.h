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

    //Implement TableListBoxModel
    //==============================================
    /**
    * Overrides default getNumRows function, to get current number of rows in the table
    * @param
    * @return {int} current number of rows in the table
    */
    int getNumRows() override;
    /**
    * Overrides default paintRowBackground function, to paint background of each row in the table
    * @param {Graphics&} g
    * @param {int} rowNumber : row number
    * @param {int} width
    * @param {int} height
    * @param {bool} rowIsSelected : whether the row is selected
    * @return
    */
    void paintRowBackground(Graphics& g,
                        int rowNumber,
                        int width,
                        int height,
                        bool rowIsSelected) override;
    /**
    * Overrides default paintCell function, to paint each cell in the table
    * @param {Graphics&} g
    * @param {int} rowNumber : row number of the cell
    * @param {int} columnId : column id of the cell
    * @param {int} width
    * @param {int} height
    * @param {bool} rowIsSelected : whether the row is selected
    * @return
    */
    void paintCell(Graphics& g, 
                int rowNumber, 
                int columnId, 
                int width, 
                int height, 
                bool rowIsSelected) override;
    /**
    * Overrides default refreshComponentForCell function, to create or update a custom component to go in a cell
    * @param {int} rowNumber : row number of the cell
    * @param {int} columnId : column id of the cell
    * @param {bool} rowIsSelected : whether the row is selected
    * @param {Component*} existingComponentToUpdate : if existing then update, if null then create
    * @return {Component*} the custom component created/updated in a cell
    */
    Component* refreshComponentForCell(int rowNumber,
                            int columnId,
                            bool isRowSelected,
                            Component* existingComponentToUpdate) override;
    /**
    * Overrides default deleteKeyPressed event handler
    * @param {int} lastRowSelected : last selected row number
    * @return
    */
    void deleteKeyPressed(int lastRowSelected) override;
    /**
    * Overrides default sortOrderChanged event handler
    * @param {int} newSortColumnId : column id of the column to be sorted
    * @param {bool} isForwards : sort in ascending or descending order
    * @return
    */
    void sortOrderChanged(int newSortColumnId, bool isForwards) override;

    //Implement Button::Listener
    //==============================================
    /**
    * Overrides default buttonClicked event handler
    * @param {Button*} button
    * @return
    */
    void buttonClicked(Button* button) override;

    /**
    * Add the input file to playlist
    * @param {File*} file
    * @return {bool} : whether adding to playlist is successful
    */
    bool pushFileToPlaylist(File* file);
    /**
    * Returns duration of the audio file
    * @param {File*} file
    * @param {AudioFormatManager*} fm
    * @return {double} : duration of the audio file
    */
    static double getAudioFileDuration(File* file, AudioFormatManager* fm);
    /**
    * Returns universal url of the audio file
    * @param {String} path
    * @return {String} : universal url of the audio file
    */
    static String toUniversalURL(String path);
    /**
    * Refreshes the playlist
    * @param {bool} deleteNonExistingFiles : whether delete non existing audio files during refreshing
    * @return
    */
    void refresh(bool deleteNonExistingFiles = true);
    /**
    * Returns whether the specified file is on the playlist
    * @param {File*} file : input file
    * @return {bool} : whether the specified file is on the playlist
    */
    bool isFileOnList(File* file);
    /**
    * Read playlist file contents from the input file
    * @param {File*} file : input file
    * @return {bool} : whether the reading is successful
    */
    bool readFromFile(File* file);
    /**
    * Write playlist contents to the output file
    * @param {File*} file : output file
    * @return {bool} : whether the writing is successful
    */
    bool writeToFile(File* file);
    /**
    * Save the playlist to the temporary data file (./{appName}.data)
    * @param {File*} file : output file
    * @param {bool} notificationOn : whether notification should be on for informing successful saving or errors
    * @return
    */
    void saveToTempFile(bool notificationOn = true);
    /**
    * Load the playlist from the temporary data file (./{appName}.data)
    * @param
    * @return
    */
    void loadFromTempFile();
    /**
    * Sort the playlist by selected column
    * @param {String} sortBy : sort the playlist by which column, expecting name / ext / len
    * @param {bool} asending : whether sort in asending or descending order
    * @return
    */
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
