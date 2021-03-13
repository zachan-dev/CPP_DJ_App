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

    //Implement Button::Listener
    //==============================================
    /**
    * Overrides default button onclick event handler function
    * @param  {Button*} button
    * @return
    */
    void buttonClicked(Button* button) override;

    //Implement TextEditor::Listener
    //==============================================
    /**
    * Overrides default textEditor onChange event handler function
    * @param  {TextEditor*} textEditor
    * @return
    */
    void textEditorTextChanged(TextEditor& textEditor) override;

    /**
    * Save library audio file paths to temp file, using PlaylistComponent
    * @param
    * @return
    */
    void saveToTempFile();
    /**
    * Load library audio file paths from temp file, using PlaylistComponent
    * @param
    * @return
    */
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
