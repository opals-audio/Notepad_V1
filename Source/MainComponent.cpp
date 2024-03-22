#include "MainComponent.h"
/*Todo:
    Look into Cmake & JUCE
    Text input box - write to file
    Display text with formatting
*/


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

    textButton.setSize(150, 50);https://docs.juce.com/master/classUndoManager.html
    textButton.setTopLeftPosition(label.getX(), label.getBottom() + 50);
    textButton.setButtonText("Whats the time??");
    textButton.addListener(this);
    addAndMakeVisible(textButton);

    textEditor.setSize(400, 50);
    textEditor.setTextToShowWhenEmpty("Type Here",juce::Colours::grey);
    textEditor.onReturnKey = [this]
        {
            auto newText = textEditor.getText();
            changeFileText(newText);
            textEditor.clear();
        };
    addAndMakeVisible(textEditor);

    //Clear String 
    myContent.clear();
    //Load file contents into myFile and verify exists
    myFile = juce::File::getCurrentWorkingDirectory().getChildFile("file.txt");
    if (!myFile.existsAsFile())
    {
        DBG("File Doesn't Exist...");
    }
    std::unique_ptr<juce::FileOutputStream> output = myFile.createOutputStream();
    if (!output->openedOk())
    {
        DBG("Failed To Open File");
    }
    bool readWholeFile = true;

    //Clear File Text (for now)
    if (readWholeFile)
    {
        auto& stream = output;
        stream->setPosition(0);
        stream->truncate();
        displayFileText();
    }
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
    std::unique_ptr<juce::FileOutputStream> output = myFile.createOutputStream();
    if (!output->openedOk())
    {
        DBG("Failed To Open File");
    }
    bool readWholeFile = true;

    if (readWholeFile)
    {
        auto& stream = output;
        stream->setPosition(0);
        stream->truncate();
        stream->writeText(juce::Time::getCurrentTime().toString(1,1,1,1),0,0,nullptr);
        stream->flush();
        displayFileText();
    }
}

void MainComponent::changeFileText(juce::String stringToAdd)
{
    std::unique_ptr<juce::FileOutputStream> output = myFile.createOutputStream();
    if (!output->openedOk())
    {
        label.setText("Problem Writing To File! :(", juce::NotificationType::dontSendNotification);
    }
    bool readWholeFile = true;

    if (readWholeFile)
    {
        //output->setPosition(0);
        //output->truncate();
        output->writeText(stringToAdd, 0, 0, "\r\n");
        output->flush();
        displayFileText();
    }
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