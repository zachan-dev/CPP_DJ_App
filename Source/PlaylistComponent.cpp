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
PlaylistComponent::PlaylistComponent()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

    trackTitles.push_back("Track 1");
    trackTitles.push_back("Track 2");
    trackTitles.push_back("Track 3");
    trackTitles.push_back("Track 4");
    trackTitles.push_back("Track 5");
    trackTitles.push_back("Track 6");

    tableComponent.getHeader().addColumn("Track title", 1, 400);
    tableComponent.getHeader().addColumn("", 2, 400);

    tableComponent.setModel(this);

    addAndMakeVisible(tableComponent);

}

PlaylistComponent::~PlaylistComponent()
{
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
    tableComponent.getHeader().setColumnWidth(1, getWidth() / 2);
    tableComponent.getHeader().setColumnWidth(2, getWidth() / 2);
}

//Implement TableListBoxModel
//==============================================
int PlaylistComponent::getNumRows() {
    return trackTitles.size();
};
void PlaylistComponent::paintRowBackground(Graphics& g, 
                                    int rowNumber, 
                                    int width, 
                                    int height, 
                                    bool rowIsSelected) 
{
    if (rowIsSelected) {
        g.fillAll(Colours::orange);
    }
    else {
        g.fillAll(Colours::darkgrey);
    }
};
void PlaylistComponent::paintCell(Graphics& g, 
                                int rowNumber, 
                                int columnId, 
                                int width, 
                                int height, 
                                bool rowIsSelected)
{
    if (rowNumber < getNumRows()) {
        g.drawText(trackTitles[rowNumber],
            2, 0, width - 4, height,
            Justification::centredLeft, true);
    }
};
Component* PlaylistComponent::refreshComponentForCell(int rowNumber,
                                int columnId,
                                bool isRowSelected,
                                Component* existingComponentToUpdate)
{
    if (columnId == 2) { // playbuttons column
        if (existingComponentToUpdate == nullptr) {
            TextButton* btn = new TextButton{ "play" };
            String id{ std::to_string(rowNumber) };
            btn->setComponentID(id);

            btn->addListener(this);
            existingComponentToUpdate = btn;
        }
    }
    return existingComponentToUpdate;
}

void PlaylistComponent::buttonClicked(Button* button)
{
    int id = std::stoi(button->getComponentID().toStdString());
    DBG("PlaylistComponent::buttonClicked " + trackTitles[id]);
}