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

        FileChooser chooser{ "Select a file..." };
        do {
            if (chooser.browseForFileToOpen()) // will return true if user choose >= 1 files
            {
                File* file = new File(chooser.getResult());
                if (playlistComponent.pushFileToPlaylist(file)) {
                    // success
                    playlistComponent.refresh(); // refresh the list
                    break; // break the do loop
                }
            }
            else break; // break the do loop if cancwel
        } while (true);
    }
    if (button == &exportButton)
    {
        DBG("MusicLibrary::buttonClicked Export Button was clicked.");
    }
    if (button == &importButton)
    {
        DBG("MusicLibrary::buttonClicked Import Button was clicked.");
    }
}