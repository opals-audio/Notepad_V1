#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent  : public juce::Component, juce::Button::Listener
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void displayFileText();
    void changeFileText();
    void buttonClicked(juce::Button*) override;

private:
    //==============================================================================
    // Your private member variables go here...
    juce::Label label;
    juce::File myFile;
    juce::String myContent;
    juce::TextButton textButton;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
