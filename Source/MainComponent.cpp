#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    setSize (600, 400);

    //Set Label
    label.setSize(300, 200);
    addAndMakeVisible(label);
    label.setTopLeftPosition(150, 100);
    label.setColour(0x1000282, juce::Colours::white);
    label.setText("Hello World", juce::NotificationType::dontSendNotification);
    label.setJustificationType(juce::Justification::centred);

    textButton.setSize(150, 50);
    addAndMakeVisible(textButton);
    textButton.setTopLeftPosition(label.getX(), label.getBottom() + 50);
    textButton.setButtonText("Whats the time??");
    textButton.addListener(this);

    //Clear String 
    myContent.clear();
    //Load file contents into myFile and verify exists
    myFile = juce::File::getCurrentWorkingDirectory().getChildFile("file.txt");
    if (!myFile.existsAsFile())
    {
        DBG("File Doesn't Exist...");
    }

    displayFileText();
    }
 
MainComponent::~MainComponent()
{
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
        g.setFont (juce::Font (16.0f));
    g.setColour (juce::Colours::white);
}

void MainComponent::resized()
{

}

void MainComponent::buttonClicked(juce::Button* button)
{
    auto output = myFile.createOutputStream();
    if (!output->openedOk())
    {
        DBG("Failed To Open File");
    }
    bool readWholeFile = true;

    if (readWholeFile)
    {
        auto stream = output.get();
        stream->setPosition(0);
        stream->truncate();
        stream->writeText(juce::Time::getCurrentTime().toString(1,1,1,1),0,0,nullptr);
        stream->flush();
        displayFileText();
    }
}

void MainComponent::changeFileText()
{

}

void MainComponent::displayFileText()
{
    //Open input and check opened ok - set safety bool true 
    std::unique_ptr<juce::FileInputStream> input(myFile.createInputStream());
    if (!input->openedOk())
    {
        DBG("Failed To Open File");
    }
    bool readWholeFile = true;

    if (readWholeFile)
    {
        myContent = input->readString();
        label.setText(myContent, juce::NotificationType::dontSendNotification);
    }
    else
    {
        label.setText("Problem Reading File :(", juce::NotificationType::dontSendNotification);
    }
}


//juce::FileOutputStream output (myFile);
//output.writeText("Some Text",0,0,"\n");
//output.flush();