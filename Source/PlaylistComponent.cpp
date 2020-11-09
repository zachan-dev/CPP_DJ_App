/*
  ==============================================================================

    PlaylistComponent.cpp
    Created: 6 Nov 2020 1:48:10am
    Author:  chans

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PlaylistComponent.h"

//==============================================================================
PlaylistComponent::PlaylistComponent(TracksManager* tm)
    : tracksManager{tm}
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

    // load init files
    loadFilesFromMemory();

    // please also update columnsNum
    tableComponent.getHeader().addColumn("File name", 1, 400);
    tableComponent.getHeader().addColumn("Extension", 2, 400);
    tableComponent.getHeader().addColumn("Length (HH:mm:ss)", 3, 400);
    tableComponent.getHeader().addColumn("", 4, 400);

    // give it a border
    tableComponent.setColour(ListBox::outlineColourId, Colours::grey);
    tableComponent.setOutlineThickness(1);

    tableComponent.getHeader().setSortColumnId(1, true); // sort forwards by the Name column
    tableComponent.setMultipleSelectionEnabled(true);


    tableComponent.setModel(this);

    addAndMakeVisible(tableComponent);

}

PlaylistComponent::~PlaylistComponent()
{
    for (auto& file : trackFiles) {
        delete file;
        file = nullptr;
    }
}

void PlaylistComponent::paint (Graphics& g)
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
    g.drawText ("PlaylistComponent", getLocalBounds(),
                Justification::centred, true);   // draw some placeholder text
}

void PlaylistComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    tableComponent.setBounds(0, 0, getWidth(), getHeight());

    for (int i = 1; i <= columnsNum; ++i) {
        tableComponent.getHeader().setColumnWidth(i, getWidth() / columnsNum);
    }
}

//Implement TableListBoxModel
//==============================================
int PlaylistComponent::getNumRows() {
    return trackFiles.size();
};
void PlaylistComponent::paintRowBackground(Graphics& g, 
                                    int rowNumber, 
                                    int width, 
                                    int height, 
                                    bool rowIsSelected) 
{
    auto alternateColour = getLookAndFeel().findColour(ListBox::backgroundColourId)
        .interpolatedWith(getLookAndFeel().findColour(ListBox::textColourId), 0.03f);
    if (rowIsSelected)
        g.fillAll(Colours::lightblue);
    else if (rowNumber % 2)
        g.fillAll(alternateColour);
};
void PlaylistComponent::paintCell(Graphics& g, 
                                int rowNumber, 
                                int columnId, 
                                int width, 
                                int height, 
                                bool rowIsSelected)
{
    if (rowIsSelected) {
        g.setColour(Colours::black);
    }
    else {
        g.setColour(getLookAndFeel().findColour(ListBox::textColourId));
    }

    if (rowNumber < getNumRows()) {
        if (columnId == 1) { // file name Column
            g.drawText(trackFiles[rowNumber]->getFileNameWithoutExtension(),
                2, 0, width - 4, height,
                Justification::centredLeft, true);
        }
        if (columnId == 2) { // extension Column
            std::string extension = trackFiles[rowNumber]->getFileExtension().toUpperCase().toStdString();
            extension.erase(std::remove(extension.begin(), extension.end(), '.'), extension.end());
            g.drawText(extension,
                2, 0, width - 4, height,
                Justification::centredLeft, true);
        }
        if (columnId == 3) { // audio file length Column
            double durationInSec = getAudioFileDuration(trackFiles[rowNumber], &(tracksManager->formatManager));
            time_t seconds(durationInSec); // you have to convert your input_seconds into time_t
            tm* p = gmtime(&seconds); // convert to broken down time
            char durationInISO[80];
            strftime(durationInISO, 80, "%H:%M:%S", p); // convert seconds to ISO8601
            g.drawText(durationInISO,
                2, 0, width - 4, height,
                Justification::centredLeft, true);
        }
    }

    g.setColour(getLookAndFeel().findColour(ListBox::backgroundColourId));
    g.fillRect(width - 1, 0, 1, height);
};
Component* PlaylistComponent::refreshComponentForCell(int rowNumber,
                                int columnId,
                                bool isRowSelected,
                                Component* existingComponentToUpdate)
{
    if (columnId == 4) { // playbuttons column
        if (existingComponentToUpdate == nullptr) {
            TextButton* btn = new TextButton{ "play" };
            String id{ std::to_string(rowNumber) };
            btn->setComponentID(id);

            btn->addListener(this);
            existingComponentToUpdate = btn;
        }
    }
    else {
        jassert(existingComponentToUpdate == nullptr);
        return nullptr;
    }
    return existingComponentToUpdate;
}

void PlaylistComponent::buttonClicked(Button* button)
{
    // Play buttons clicked
    int fileId = std::stoi(button->getComponentID().toStdString());
    DBG("PlaylistComponent::buttonClicked " + trackFiles[fileId]->getFileNameWithoutExtension());
    DBG("PlaylistComponent::buttonClicked " + trackFiles[fileId]->getFullPathName());

    int trackID = -1;
    StringArray availableTrackIDs = tracksManager->getAvaliableTrackNumbers();
    if (availableTrackIDs.size() == 0) {
        AlertWindow::showMessageBoxAsync(AlertWindow::WarningIcon, ProjectInfo::projectName,
            "No Avaliable Tracks to play. Please add at least a track first.",
            "OK");
        return;
    }

#if JUCE_MODAL_LOOPS_PERMITTED
    AlertWindow w(ProjectInfo::projectName,
        "Please choose an avaliable track to play the audio file:",
        AlertWindow::QuestionIcon);

    w.addComboBox("option", availableTrackIDs, "Avaliable Track Number");
    w.addButton("OK", 1, KeyPress(KeyPress::returnKey, 0, 0));
    w.addButton("Cancel", 0, KeyPress(KeyPress::escapeKey, 0, 0));

    if (w.runModalLoop() != 0) // is they picked 'ok'
    {
        // this is the item they chose in the drop-down list..
        trackID = std::stoi(availableTrackIDs[w.getComboBoxComponent("option")->getSelectedItemIndex()].toStdString());
    }
#endif

    if (trackID == -1)
    {
        DBG("Select track number unsuccessful!");
    }

    if (!trackFiles[fileId]->exists()) {
        DBG("PlaylistComponent::buttonClicked File does not exist anymore!");
        AlertWindow::showMessageBoxAsync(AlertWindow::WarningIcon, ProjectInfo::projectName,
            "This audio file does not exist anymore!\n\nRescanning the files and removing non-existing files on the playlist...",
            "OK");
        refresh();
        return;
    }

    String pathStr = trackFiles[fileId]->getFullPathName();
    pathStr = toUniversalURL(pathStr);

    URL& filePath = URL(pathStr);
    Track* track = tracksManager->getTrackUsingID(trackID);
    if (track == nullptr) {
        DBG("PlaylistComponent::buttonClicked Unable to retrieve track");
        return;
    }
    if (!track->deckGUI.isVisible()) {
        DBG("PlaylistComponent::buttonClicked That track is not visible yet!");
        return;
    }
    if (track->deckGUI.loadURL(filePath)) {
        DBG("PlaylistComponent::buttonClicked Track loading successful!");
    }
    else {
        DBG("PlaylistComponent::buttonClicked Track loading unsuccessful!");
    }
}

void PlaylistComponent::loadFilesFromMemory()
{
    std::string parent_path = "C:\\Users\\chans\\Music\\tracks_example";
    for (int i = 1; i <= 5; ++i) {
        File* file = new File(parent_path + "\\Track_" + std::to_string(i) + ".mp3");
        if (!pushFileToPlaylist(file)) {
            delete file;
        }
    }
}

bool PlaylistComponent::pushFileToPlaylist(File* file)
{
    std::vector<AudioFormat*> knownFormats;
    for (int i = 0; i < tracksManager->formatManager.getNumKnownFormats(); ++i)
    {
        knownFormats.push_back(tracksManager->formatManager.getKnownFormat(i));
    }

    bool validFile = false;
    for (auto& knownFormat : knownFormats) {
        if (knownFormat->canHandleFile(*file)) {
            validFile = true;
            break;
        }
    }
    if (!validFile) {
        AlertWindow::showMessageBox(AlertWindow::WarningIcon, ProjectInfo::projectName,
            "Load file failed.\nPlease choose a file with suitable audio format.");
    }

    bool existFile = file->exists();
    if (!existFile) {
        AlertWindow::showMessageBox(AlertWindow::WarningIcon, ProjectInfo::projectName,
            "Load file failed.\nFile does not exist!\n\nPath: " + file->getFullPathName());
    }

    bool onListFile = isFileOnList(file);
    if (onListFile) {
        AlertWindow::showMessageBox(AlertWindow::WarningIcon, ProjectInfo::projectName,
            "Load file failed.\nFile is already on the playlist.\n\nFile Name: " + file->getFileNameWithoutExtension());
    }

    if (validFile && existFile && !onListFile) {
        trackFiles.push_back(file);
        repaint();
        return true;
    }
    else {
        DBG("File to put into Playlist does not exist.");
        return false;
    }
}

double PlaylistComponent::getAudioFileDuration(File* file, AudioFormatManager* fm)
{
    auto* reader = fm->createReaderFor(&(FileInputStream(*file)));
    return reader->lengthInSamples / reader->sampleRate;
}

String PlaylistComponent::toUniversalURL(String path)
{
    String subfix = path.replace("\\", "//");
    String prefix = "file:///";
    return (subfix.toLowerCase().contains(prefix)) ? subfix : prefix + subfix;
}

void PlaylistComponent::refresh()
{
    std::vector<File*> tempTrackFiles = trackFiles; // deep copy
    trackFiles = {};
    for (auto& file : tempTrackFiles)
    {
        if (!pushFileToPlaylist(file)) delete file;
    }
    repaint();
    tableComponent.updateContent();
}

bool PlaylistComponent::isFileOnList(File* file)
{
    for (auto& trackFile : trackFiles)
    {
        if (trackFile == file) return true;
    }
    return false;
}