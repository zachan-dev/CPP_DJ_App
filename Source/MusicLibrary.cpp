/*
  ==============================================================================

    MusicLibrary.cpp
    Created: 9 Nov 2020 5:27:45pm
    Author:  chans

  ==============================================================================
*/

#include <JuceHeader.h>
#include "MusicLibrary.h"

//==============================================================================

MusicLibrary::MusicLibrary(TracksManager* tm)
    : tracksManager{ tm }
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

    // init load temp file to the playlist
    loadFromTempFile();

    addAndMakeVisible(playlistComponent);
    addAndMakeVisible(loadSaveButton);
    addAndMakeVisible(exportButton);
    addAndMakeVisible(importButton);
    addAndMakeVisible(searchTextbox);
    searchTextbox.setText("");
    searchTextbox.setTextToShowWhenEmpty("Search by name...", Colours::limegreen);

    // register listeners
    loadSaveButton.addListener(this);
    exportButton.addListener(this);
    importButton.addListener(this);
    searchTextbox.addListener(this);
}

MusicLibrary::~MusicLibrary()
{
}

void MusicLibrary::paint (Graphics& g)
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
    g.drawText ("MusicLibrary", getLocalBounds(),
                Justification::centred, true);   // draw some placeholder text
}

void MusicLibrary::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    
    double buttonsHeight = getHeight() / 5;
    double buttonsWidth = getWidth() / 4;

    double textboxPadding = buttonsHeight / 8;
    double textboxHeight = buttonsHeight - 2 * textboxPadding;
    double textboxWidth = buttonsWidth - 2 * textboxPadding;

    loadSaveButton.setBounds(0, 0, buttonsWidth, buttonsHeight);
    exportButton.setBounds(buttonsWidth, 0, buttonsWidth, buttonsHeight);
    importButton.setBounds(2 * buttonsWidth, 0, buttonsWidth, buttonsHeight);
    searchTextbox.setBounds(3 * buttonsWidth + textboxPadding, textboxPadding, textboxWidth, textboxHeight);
    searchTextbox.applyFontToAllText(Font(textboxHeight * 0.6f));

    playlistComponent.setBounds(0, buttonsHeight, getWidth(), 4 * buttonsHeight);
}


//Implement Button::Listener
//==============================================
void MusicLibrary::buttonClicked(Button* button)
{
    if (button == &loadSaveButton)
    {
        DBG("MusicLibrary::buttonClicked Load & Save Button was clicked.");

        // Load
        bool loaded = false;
        FileChooser chooser{ "Select file(s)..." };
        do {
            if (chooser.browseForMultipleFilesToOpen()) // will return true if user choose >= 1 files
            {
                for (auto& chooserRes : chooser.getResults())
                {
                    File* file = new File(chooserRes);
                    if (playlistComponent.pushFileToPlaylist(file)) {
                        // success
                        playlistComponent.refresh(); // refresh the list
                        loaded = true;
                    }
                }
            }
            else break; // break the do loop if cancel
        } while (!loaded);

        if (loaded) {
            saveToTempFile();
        }
    }
    if (button == &exportButton)
    {
        DBG("MusicLibrary::buttonClicked Export Button was clicked.");

        //Export
        FileChooser chooser{ "Save to file...", 
                             File(),
                             "*" + PlaylistComponent::TEMP_FILEEXT };
        if (chooser.browseForFileToSave(true))
        {
            File* file = new File(chooser.getResult());
            if (playlistComponent.writeToFile(file)) {
                AlertWindow::showMessageBox(AlertWindow::InfoIcon, ProjectInfo::projectName,
                    "Export successfully");
            }
            else {
                AlertWindow::showMessageBox(AlertWindow::WarningIcon, ProjectInfo::projectName,
                    "Error while exporting Playlist");
            }
            delete file; // release memory
        }
    }
    if (button == &importButton)
    {
        DBG("MusicLibrary::buttonClicked Import Button was clicked.");

        //Import
        FileChooser chooser{ "Save to file...",
                             File(),
                             "*" + PlaylistComponent::TEMP_FILEEXT };
        if (chooser.browseForFileToOpen())
        {
            File* file = new File(chooser.getResult());
            if (playlistComponent.readFromFile(file)) {
                AlertWindow::showMessageBox(AlertWindow::InfoIcon, ProjectInfo::projectName,
                    "Import successfully");
                saveToTempFile();
            }
            else {
                AlertWindow::showMessageBox(AlertWindow::WarningIcon, ProjectInfo::projectName,
                    "Error while importing Playlist");
            }
            delete file; // release memory
        }
    }
}

//Implement TextEditor::Listener
//==============================================
void MusicLibrary::textEditorTextChanged(TextEditor& textEditor)
{
    if (&textEditor == &searchTextbox) {
        String searchText = textEditor.getText();

        DBG("MusicLibrary::textEditorTextChanged, Value: " + searchText);
        playlistComponent.searchResults.clear(); // clear previous searchResults

        if (searchText.isNotEmpty()) {
            for (auto& trackFile : playlistComponent.trackFiles)
            {
                if (trackFile->getFileName().trim().toLowerCase().contains(searchText.trim().toLowerCase())) { // found a match
                    playlistComponent.searchResults.push_back(trackFile);
                }
            }
        }

        playlistComponent.refresh(false);
    }
}

void MusicLibrary::saveToTempFile()
{
     playlistComponent.saveToTempFile();
}

void MusicLibrary::loadFromTempFile()
{
    playlistComponent.loadFromTempFile();
}