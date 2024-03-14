#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    setSize (600, 400);
    DBG("Current Working Directory : " <<juce::File::getCurrentWorkingDirectory().getFullPathName());
    
    juce::File myFile(juce::File::getCurrentWorkingDirectory().getChildFile("file.txt"));
    juce::String myContent;
    myContent.clear();

    if (!myFile.existsAsFile())
    {
        DBG("File Doesn't Exist...");
    }

    juce::FileOutputStream output (myFile);
    output.writeText("Some Text",0,0,"\\n");

    std::unique_ptr<juce::FileInputStream> input (myFile.createInputStream());

    if (!input->openedOk())
    {
        DBG("Failed To Open File");
    }

    bool readWholeFile = true;

    if (readWholeFile)
    {
        myContent = input->readString();
    }

    DBG(myContent);

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