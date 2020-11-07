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

//==============================================================================
/*
*/
class PlaylistComponent    : public Component,
                             public TableListBoxModel,
                             public Button::Listener
{
public:
    PlaylistComponent();
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

private:

    TableListBox tableComponent;
    std::vector<std::string> trackTitles;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlaylistComponent)
};
