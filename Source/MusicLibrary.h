/*
  ==============================================================================

    MusicLibrary.h
    Created: 9 Nov 2020 5:27:45pm
    Author:  chans

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "TracksManager.h"
#include "PlaylistComponent.h"

//==============================================================================
/*
*/
class MusicLibrary    : public Component,
                        public Button::Listener,
                        public TextEditor::Listener
{
public:
    MusicLibrary(TracksManager* tm);
    ~MusicLibrary();

    void paint (Graphics&) override;
    void resized() override;

    //Implement Button::Listener
    //==============================================
    void buttonClicked(Button* button) override;

    //Implement TextEditor::Listener
    //==============================================
    void textEditorTextChanged(TextEditor& textEditor) override;

    void saveToTempFile();
    void loadFromTempFile();

private:
    TextButton loadSaveButton{ "Load & Save" };
    TextButton exportButton{ "Export" };
    TextButton importButton{ "Import" };
    TextEditor searchTextbox;

    TracksManager* tracksManager;
    PlaylistComponent playlistComponent{ tracksManager, &searchTextbox };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MusicLibrary)
};
