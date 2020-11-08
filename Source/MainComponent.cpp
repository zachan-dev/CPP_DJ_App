/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    // Make sure you set the size of the component after
    // you add any child components.
    setSize (800, 600);

    // Some platforms require permissions to open input channels so request that here
    if (RuntimePermissions::isRequired (RuntimePermissions::recordAudio)
        && ! RuntimePermissions::isGranted (RuntimePermissions::recordAudio))
    {
        RuntimePermissions::request (RuntimePermissions::recordAudio,
                                     [&] (bool granted) { if (granted)  setAudioChannels (2, 2); });
    }
    else
    {
        // Specify the number of input and output channels that we want to open
        setAudioChannels (2, 2);
    }

    addAndMakeVisible(tracksManager);
    addAndMakeVisible(playlistComponent);
}

MainComponent::~MainComponent()
{
    // This shuts down the audio device and clears the audio source.
    shutdownAudio();
}

//==============================================================================
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    // This function will be called when the audio device is started, or when
    // its settings (i.e. sample rate, block size, etc) are changed.

    // You can use this function to initialise any resources you might need,
    // but be careful - it will be called on the audio thread, not the GUI thread.

    // For more details, see the help for AudioProcessor::prepareToPlay()

    tracksManager.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void MainComponent::getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill)
{
    // pass the job to transportSource (with speed control) or resampleSource (with speed control)
    //transportSource.getNextAudioBlock(bufferToFill);
    //resampleSource.getNextAudioBlock(bufferToFill);

    /*player1.getNextAudioBlock(bufferToFill);
    player2.getNextAudioBlock(bufferToFill);*/

    tracksManager.getNextAudioBlock(bufferToFill);
}

//void MainComponent::getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill)
//{
//    // Your audio-processing code goes here!
//
//    // For more details, see the help for AudioProcessor::getNextAudioBlock()
//
//    // Right now we are not producing any data, in which case we need to clear the buffer
//    // (to prevent the output of random noise)
//    //bufferToFill.clearActiveBufferRegion();
//
//    // I want channel 0, start writing at this sample
//    auto* leftChan = bufferToFill.buffer->getWritePointer(0, bufferToFill.startSample);
//    auto* rightChan = bufferToFill.buffer->getWritePointer(1, bufferToFill.startSample);
//    
//    for (auto i = 0; i < bufferToFill.numSamples; ++i) {
//        //double sample = rand.nextDouble() * 0.25; // smaller range
//        //double sample = fmod(phase, 0.2); // triangle waveform
//        double sample = sin(phase) * 0.1; // purer waveform
//
//        leftChan[i] = sample;
//        rightChan[i] = sample;
//
//        phase += dphase; //pitch, 0.05 very high, 0.005 ok
//    }
//}

void MainComponent::releaseResources()
{
    // This will be called when the audio device stops, or when it is being
    // restarted due to a setting change.

    // For more details, see the help for AudioProcessor::releaseResources()
    //transportSource.releaseResources();

    tracksManager.releaseResources();
}

//==============================================================================
void MainComponent::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    // You can add your drawing code here!
    // App Watermark
    g.setFont(20.0f);
    g.drawText("OtoDesks", getLocalBounds(),
    Justification::centred, true);
}

void MainComponent::resized()
{
    // This is called when the MainContentComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
    DBG("MainComponent::resized"); // debug line

    tracksManager.setBounds(0, 0, getWidth(), getHeight() / 2);
    playlistComponent.setBounds(0, getHeight() / 2, getWidth(), getHeight() / 2);
}