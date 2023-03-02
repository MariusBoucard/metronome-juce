/*
  ==============================================================================

   This file is part of the JUCE tutorials.
   Copyright (c) 2020 - Raw Material Software Limited

   The code included in this file is provided under the terms of the ISC license
   http://www.isc.org/downloads/software-support-policy/isc-license. Permission
   To use, copy, modify, and/or distribute this software for any purpose with or
   without fee is hereby granted provided that the above copyright notice and
   this permission notice appear in all copies.

   THE SOFTWARE IS PROVIDED "AS IS" WITHOUT ANY WARRANTY, AND ALL WARRANTIES,
   WHETHER EXPRESSED OR IMPLIED, INCLUDING MERCHANTABILITY AND FITNESS FOR
   PURPOSE, ARE DISCLAIMED.

  ==============================================================================
*/

/*******************************************************************************
 The block below describes the properties of this PIP. A PIP is a short snippet
 of code that can be read by the Projucer and used to generate a JUCE project.

 BEGIN_JUCE_PIP_METADATA

 name:             SineSynthTutorial
 version:          1.0.0
 vendor:           JUCE
 website:          http://juce.com
 description:      Simple sine synthesiser.

 dependencies:     juce_audio_basics, juce_audio_devices, juce_audio_formats,
                   juce_audio_processors, juce_audio_utils, juce_core,
                   juce_data_structures, juce_events, juce_graphics,
                   juce_gui_basics, juce_gui_extra
 exporters:        xcode_mac, vs2019, linux_make

 type:             Component
 mainClass:        MainContentComponent

 useLocalCopy:     1

 END_JUCE_PIP_METADATA

*******************************************************************************/


#pragma once
#include map

//==============================================================================
class MainContentComponent   : public juce::AudioAppComponent
{
public:
    MainContentComponent()
    {
        addAndMakeVisible (BPMSlider);
        BPMSlider.setRange (30.0, 400.0,1.0);
        BPMSlider.setValue (BPM, juce::dontSendNotification);  // [6]

        BPMSlider.onValueChange = [this]
        {
           BPM = BPMSlider.getValue();
           updatetime();
        };
        
        addAndMakeVisible(numerateurSlider);
        numerateurSlider.setRange(1.0,20.0,1.0);
        numerateurSlider.setValue(4.0);
        
        numerateurSlider.onValueChange = [this]
        {
           Numerateur = numerateurSlider.getValue();
        };


        setSize (600, 100);
        setAudioChannels (0, 2); // no inputs, two outputs
    }

    ~MainContentComponent() override
    {
        shutdownAudio();
    }
    void updatetime(){
        sampleParTemps = sampleRate*denomDic[denominateur]/BPM;

    }
    void resized() override
    {
        BPMSlider.setBounds (10, 10, getWidth() - 20, 20);
        numerateurSlider.setBounds(10,50,getWidth()-20,20);
    }

    void updateAngleDelta1()
    {
        //Combien il y a de fois une periode dans un sample 0.01 si f = 441 et SampleRate = 44100
        auto cyclesPerSample = frequency1 / currentSampleRate;         // [2]
        //On multiplie pour avoir un angle en radian par lequel on va pouvoir incrémenter
        angleDelta1 = cyclesPerSample * 2.0 * juce::MathConstants<double>::pi;          // [3]
    }


    void updateAngleDelta2()
    {
        //Combien il y a de fois une periode dans un sample 0.01 si f = 441 et SampleRate = 44100
        auto cyclesPerSample = frequency2 / currentSampleRate;         // [2]
        //On multiplie pour avoir un angle en radian par lequel on va pouvoir incrémenter
        angleDelta2 = cyclesPerSample * 2.0 * juce::MathConstants<double>::pi;          // [3]
    }

        //Le sample rate est tjr dans l'appelle de prepare to play -> called before the firs next audio block
    void prepareToPlay (int, double sampleRate) override
    {
        currentSampleRate = sampleRate;
        updateAngleDelta1();
        updateAngleDelta2();
    }

    void releaseResources() override {}

    //audio Block size depend on the hardware and on how it is configured
    void getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill) override
    {///////////////////////////////////////
        ////
        ////        -> HAVE TO CHECK SAMPLE VARIABLE TO USE THE POSITION
        ////
        //////////////////////////////////



        auto* leftBuffer  = bufferToFill.buffer->getWritePointer (0, bufferToFill.startSample);
        auto* rightBuffer = bufferToFill.buffer->getWritePointer (1, bufferToFill.startSample);

	if(nbBlocASauter > 0 and sampleAEcrire ==0){
        nbBlocASauter--;
        //bufferToFill.clear();
    }
    else if(sampleAEcrire>0){
        nbBlocASauter--;
        if(sampleAEcrire<bufferToFill.numSamples){
            for(int i =0; i<sampleAEcrire;i++){
                   for(int i =0;i<bufferToFill.numSamples;++i){
                        if(noteJouee==0){
                            auto currentSample = (float) std::sin (currentAngle1);
                            currentAngle1 += angleDelta1;
                            leftBuffer[sample]  = currentSample * level;
                            rightBuffer[sample] = currentSample * level;
                        }
                        else{
                            auto currentSample = (float) std::sin (currentAngle2);
                            currentAngle2 += angleDelta2;
                            leftBuffer[sample]  = currentSample * level;
                            rightBuffer[sample] = currentSample * level; 
                        } 
                }
            sampleAEcrire=0;
        }
        else{
            sampleAEcrire-=bufferToFill.numSamples;
            for(int i=0;i<bufferToFill.numSamples,i++){
                 if(noteJouee==0){
                            auto currentSample = (float) std::sin (currentAngle1);
                            currentAngle1 += angleDelta1;
                            leftBuffer[sample]  = currentSample * level;
                            rightBuffer[sample] = currentSample * level;
                        }
                        else{
                            auto currentSample = (float) std::sin (currentAngle2);
                            currentAngle2 += angleDelta2;
                            leftBuffer[sample]  = currentSample * level;
                            rightBuffer[sample] = currentSample * level; 
                        } 
            }

        }
    }
    else if(nbBlocASauter==0){
        noteJouee = (noteJouee+1)%Numerateur;

        for(int i =0;i<SampleAPasser;i++){
            //PASSSAMPLE
        }
        //BLOCSIZE ????
        int passBlocTmp = sampleParTemps - //RESTEDUBUFFER //BLOCSIZE
        nbBlocASauter = passBlocTmp/ //BlocSize;
        SampleAPasser = passBlocTmp% //BLOCSIZE;
        sampleAEcrire = dureeSonSample;

        if(sampleAEcrire</* RESTEBUFFER*/){
            for(int i =0;i<sampleAEcrire;i++){
                if(noteJouee==0){

                }
                else{

                }

                //BALANCELESON
            }
            sampleAEcrire=0;
        }
        else{
            sampleAEcrire-=//RESTEBUFFER
            for(int i =0;i<bufferToFill.numSamples;++i){
                if(noteJouee==0){
                    auto currentSample = (float) std::sin (currentAngle1);
                    currentAngle1 += angleDelta1;
                    leftBuffer[sample]  = currentSample * level;
                    rightBuffer[sample] = currentSample * level;
                }
                else{
                    auto currentSample = (float) std::sin (currentAngle2);
                    currentAngle2 += angleDelta2;
                    leftBuffer[sample]  = currentSample * level;
                    rightBuffer[sample] = currentSample * level; 
                }
                //BALANCELESON
            }
        }

    }





        auto level = levelSlider.getValue();
        
        //Split les cas si freq a changée ou non
        if(localTargetFrequency != currentFrequency)
        {
        
                auto frequencyIncrement = (localTargetFrequency - currentFrequency)/ bufferToFill.numSamples;
                
                for (auto sample =0;sample < bufferToFill.numSamples;++sample)
                {
                    //why not juste taking sample number ? -> fuck it takes the value
                    //of the sin to output
                    auto currentSample = (float) std::sin (currentAngle);
                    currentFrequency += frequencyIncrement;                                                       // [9]
                    updateAngleDelta();                                                                           // [10]
                    currentAngle += angleDelta;
                    leftBuffer[sample]  = currentSample * level;
                    rightBuffer[sample] = currentSample * level;
                
                }
                currentFrequency = localTargetFrequency;
        
        }
        else
        {
        for (auto sample = 0; sample < bufferToFill.numSamples; ++sample)
        {
            auto currentSample = (float) std::sin (currentAngle);
            currentAngle += angleDelta;
            leftBuffer[sample]  = currentSample * level;
            rightBuffer[sample] = currentSample * level;
        }
        }
    }

private:
    int nbBlocASauter=0;
    int Numerateur;
    int noteJouee;
    enum denominateur {1,2,4,8,16};
    std::map<int,int> denomDic={{1:240,
                            2:120,
                            4:60,
                            8:30,
                            16:15
                            }};
    int sampleParTemps;
    int BPM=100;
    int sampleAEcrire;
    int SampleAPasser;

    double frequency1= 440.0;
    double frequency2= 360.0;

    int dureeSonSample = 4410;

    juce::Slider BPMSlider;
    juce::Slider numerateurSlider;
    juce::Slider::RotaryParameters denominateurSlider;
    //Petits attributs qui seront gardés au chaud


    double currentSampleRate = 0.0, currentAngle1 = 0.0,currentAngle2=0.0, angleDelta = 0.0; // [1]
    double currentFrequency = 500.0, targetFrequency = 500.0; // [5]
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};
