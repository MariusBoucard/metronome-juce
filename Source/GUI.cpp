/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 7.0.1

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2020 - Raw Material Software Limited.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "GUI.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
GUI::GUI ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    juce__slider.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (juce__slider.get());
    juce__slider->setRange (0, 10, 0);
    juce__slider->setSliderStyle (juce::Slider::Rotary);
    juce__slider->setTextBoxStyle (juce::Slider::TextBoxAbove, false, 80, 20);
    juce__slider->addListener (this);

    juce__slider->setBounds (32, 264, 191, 112);

    juce__slider2.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (juce__slider2.get());
    juce__slider2->setRange (0, 10, 0);
    juce__slider2->setSliderStyle (juce::Slider::IncDecButtons);
    juce__slider2->setTextBoxStyle (juce::Slider::TextBoxLeft, false, 80, 20);
    juce__slider2->addListener (this);

    juce__slider2->setBounds (72, 64, 152, 120);

    juce__comboBox.reset (new juce::ComboBox ("new combo box"));
    addAndMakeVisible (juce__comboBox.get());
    juce__comboBox->setEditableText (false);
    juce__comboBox->setJustificationType (juce::Justification::centredLeft);
    juce__comboBox->setTextWhenNothingSelected (juce::String());
    juce__comboBox->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    juce__comboBox->addListener (this);

    juce__comboBox->setBounds (312, 152, 150, 24);

    juce__comboBox2.reset (new juce::ComboBox ("new combo box"));
    addAndMakeVisible (juce__comboBox2.get());
    juce__comboBox2->setEditableText (false);
    juce__comboBox2->setJustificationType (juce::Justification::centredLeft);
    juce__comboBox2->setTextWhenNothingSelected (juce::String());
    juce__comboBox2->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    juce__comboBox2->addListener (this);

    juce__comboBox2->setBounds (392, 288, 150, 24);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

GUI::~GUI()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    juce__slider = nullptr;
    juce__slider2 = nullptr;
    juce__comboBox = nullptr;
    juce__comboBox2 = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void GUI::paint (juce::Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (juce::Colour (0xff323e44));

    {
        int x = 12, y = 4, width = 600, height = 400;
        juce::Colour fillColour = juce::Colour (0xff9fd47a);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
    }

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void GUI::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void GUI::sliderValueChanged (juce::Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == juce__slider.get())
    {
        //[UserSliderCode_juce__slider] -- add your slider handling code here..
        //[/UserSliderCode_juce__slider]
    }
    else if (sliderThatWasMoved == juce__slider2.get())
    {
        //[UserSliderCode_juce__slider2] -- add your slider handling code here..
        //[/UserSliderCode_juce__slider2]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void GUI::comboBoxChanged (juce::ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == juce__comboBox.get())
    {
        //[UserComboBoxCode_juce__comboBox] -- add your combo box handling code here..
        //[/UserComboBoxCode_juce__comboBox]
    }
    else if (comboBoxThatHasChanged == juce__comboBox2.get())
    {
        //[UserComboBoxCode_juce__comboBox2] -- add your combo box handling code here..
        //[/UserComboBoxCode_juce__comboBox2]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="GUI" componentName="" parentClasses="public juce::Component"
                 constructorParams="" variableInitialisers="" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="0" initialWidth="600"
                 initialHeight="400">
  <BACKGROUND backgroundColour="ff323e44">
    <RECT pos="12 4 600 400" fill="solid: ff9fd47a" hasStroke="0"/>
  </BACKGROUND>
  <SLIDER name="new slider" id="47a00fba8e0c0621" memberName="juce__slider"
          virtualName="" explicitFocusOrder="0" pos="32 264 191 112" min="0.0"
          max="10.0" int="0.0" style="Rotary" textBoxPos="TextBoxAbove"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="new slider" id="6bb41803e04ade29" memberName="juce__slider2"
          virtualName="" explicitFocusOrder="0" pos="72 64 152 120" min="0.0"
          max="10.0" int="0.0" style="IncDecButtons" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <COMBOBOX name="new combo box" id="6a3dce1a309af2fa" memberName="juce__comboBox"
            virtualName="" explicitFocusOrder="0" pos="312 152 150 24" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <COMBOBOX name="new combo box" id="892a0595031dbba2" memberName="juce__comboBox2"
            virtualName="" explicitFocusOrder="0" pos="392 288 150 24" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

