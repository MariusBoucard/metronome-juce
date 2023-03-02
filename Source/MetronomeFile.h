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

 name:             Metronome
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
#include <map>
#include <iostream>
//==============================================================================
//==============================================================================
class SceneComponent : public juce::AnimatedAppComponent
{
public:
	
	SceneComponent()
	{
		setFramesPerSecond(60);
		
	}
	void update() override
	{

	}
	void paint(juce::Graphics& g) override
	{
		std::cout << "paint is called" << std::endl;
		std::cout << angleMetro << std::endl;
		// (Our component is opaque, so we must completely fill the background with a solid colour)
		g.setColour(AnimatedAppComponent::getLookAndFeel().findColour(Slider::thumbColourId));       // [2]
		g.fillAll(juce::Colours::lightgrey);
		int radius = 200;

		double x = (float)getWidth() / 2.0f + (float)radius * std::cos((double)angleMetro);
		double y = ((float)getHeight() + 40) - (float)radius * std::sin((double)angleMetro);
		std::cout << "x et y :";
		std::cout << x; std::cout << y << std::endl;
		juce::Point<float> p(x, y);


		g.fillEllipse(p.x, p.y, 30.0f, 30.0f);

	}

	void resized() override
	{
		
	}
	void upangle(double angle) {
		angleMetro = angle;
	}

private:
	double angleMetro;
	//FloorComponent floor;
	//HouseComponent house;

	//==============================================================================
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SceneComponent)
};

//==============================================================================
class MainContentComponent : public juce::AudioAppComponent
{
public:
	
    MainContentComponent()
    {
        
		addAndMakeVisible(scene);
        AudioAppComponent::addAndMakeVisible (BPMSlider);
        BPMSlider.setRange (30.0, 400.0,1.0);
        BPMSlider.setValue (BPM, juce::dontSendNotification);  // [6]

        BPMSlider.onValueChange = [this]
        {
           BPM = BPMSlider.getValue();
           updatetime();
        };
        
        AudioAppComponent::addAndMakeVisible(numerateurSlider);
        numerateurSlider.setRange(1.0,20.0,1.0);
        numerateurSlider.setValue(4.0);
        
        numerateurSlider.onValueChange = [this]
        {
           Numerateur = numerateurSlider.getValue();
           updatetime();
        };

        AudioAppComponent::addAndMakeVisible(denominateur);
        denominateur.setEditableText(false);
        denominateur.setTextWhenNothingSelected(juce::String());
        denominateur.setBounds(312, 152, 150, 24);
        juce::StringArray(denom);
        denominateur.addItem(juce::String(1), 1);
        denominateur.addItem(juce::String(2), 2);
        denominateur.addItem(juce::String(4), 3);
        denominateur.addItem(juce::String(8), 4);
        denominateur.addItem(juce::String(16), 5);
        
        denominateur.onChange = [this]
        {
             d = denominateur.getSelectedId();
             updatetime();

        };

        AudioAppComponent::addAndMakeVisible(lancement);
        lancement.setButtonText("Play");
        lancement.onClick = [this] {
            if (play == 0) {
                play = 1;
                lancement.setButtonText("Stop");
            }
            else {
                play = 0;
                lancement.setButtonText("Play");
            }

        };

        
        AudioAppComponent::addAndMakeVisible(NoteUp);
        NoteUp.setRange(100.0, 5000.0, 1.0);
        NoteUp.setValue(frequency1, juce::dontSendNotification);  // [6]

        NoteUp.onValueChange = [this]
        {
            frequency1 = NoteUp.getValue();
            updateAngleDelta1();
        };

 
        AudioAppComponent::addAndMakeVisible(NoteDown);
        NoteDown.setRange(30.0, 5000.0, 1.0);
        NoteDown.setValue(frequency2, juce::dontSendNotification);  // [6]

        NoteDown.onValueChange = [this]
        {
            frequency2 = NoteDown.getValue();
            updateAngleDelta2();
        };

        AudioAppComponent::addAndMakeVisible(Level);
        Level.setRange(0, 1, 0.01);
        Level.setValue(level, juce::dontSendNotification);  // [6]

        Level.onValueChange = [this]
        {
            level = Level.getValue();
          
        };

        AudioAppComponent::setSize (600, 800);
		setAudioChannels(2, 2); // two inputs, two outputs
        
        updatetime();
        updateAngleDelta1();
        updateAngleDelta2();
        
        
    //========================================================
    //
    //AUDIO SAMPLE
    //
    //========================================================
    
    AudioAppComponent::addAndMakeVisible(openButtonUp);
    openButtonUp.setButtonText("Note Forte");
	openButtonUp.onClick = [this] { openButtonUpClicked(); };
    
     AudioAppComponent::addAndMakeVisible(openButtonDown);
    openButtonDown.setButtonText("Note faible");
	openButtonDown.onClick = [this] { openButtonDownClicked(); };
	formatManager.registerBasicFormats();

	AudioAppComponent::addAndMakeVisible(AudioSample);
	AudioSample.setTitle("Est ce que sample ?");
	
    }

    ~MainContentComponent() override
    {
        shutdownAudio();
    }
    void updatetime(){
        sampleParTemps = currentSampleRate*denomDic[d]/BPM;

    }
    void resized() override
    {
        BPMSlider.setBounds (10, 10, AudioAppComponent::getWidth() - 20, 20);
        numerateurSlider.setBounds(10,50, AudioAppComponent::getWidth()-20,20);
        denominateur.setBounds(10, 90, AudioAppComponent::getWidth() - 20, 20);
        lancement.setBounds(10, 130, AudioAppComponent::getWidth() - 20, 20);
        NoteUp.setBounds(10, 170, AudioAppComponent::getWidth() - 20, 20);
        NoteDown.setBounds(10, 210, AudioAppComponent::getWidth() - 20, 20);
        Level.setBounds(10, 250, AudioAppComponent::getWidth() - 20, 20);
		scene.setBounds(10, 290, getWidth() - 20, 200);
		openButtonUp.setBounds(10, 510, getWidth() - 20, 20);
		openButtonDown.setBounds(10, 550, getWidth() - 20, 20);
		AudioSample.setBounds(10, 600, getWidth() - 20, 20);
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
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override
    {
        currentSampleRate = sampleRate;
        updateAngleDelta1();
        updateAngleDelta2();

		
		transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
    }

    void updateAngleMetro() {
        if (aller == 0) {
			angleMetro+=(angleMin - angleMax) / sampleParTemps;
			scene.upangle(angleMetro);
        }
        else {
			
            angleMetro -= (angleMin - angleMax) / sampleParTemps;
			scene.upangle(angleMetro);
        }
    }


	void releaseResources() override
	{
		transportSource.releaseResources();
	}
    //audio Block size depend on the hardware and on how it is configured
	void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override
	{
		if (AudioSample.getToggleState() == true)
		{
			playsoundsample(bufferToFill);
			return;
		}
		if (play == 0) {
			bufferToFill.clearActiveBufferRegion();
			return;
		}

		auto sample = 0;

		auto* leftBuffer = bufferToFill.buffer->getWritePointer(0, bufferToFill.startSample);
		auto* rightBuffer = bufferToFill.buffer->getWritePointer(1, bufferToFill.startSample);

		if (nbBlocASauter > 0 && sampleAEcrire == 0) {
			//std::cout<< "Pass"<<std::endl;
			nbBlocASauter--;
			for (int i = 0; i < bufferToFill.numSamples; i++) {
				updateAngleMetro();
				leftBuffer[sample] = 0;
				rightBuffer[sample] = 0;
				sample++;
			}
			//bufferToFill.clear();
		}
		else if (sampleAEcrire > 0) {
			std::cout << "Ecrit sample" << std::endl;
			std::cout << "Bloc Size = " << std::endl;
			std::cout << bufferToFill.numSamples << std::endl;
			nbBlocASauter--;
			if (sampleAEcrire < bufferToFill.numSamples) {
				for (int i = 0; i < sampleAEcrire; i++) {
					updateAngleMetro();
					if (noteJouee == 0) {
						auto currentSample = (float)std::sin(currentAngle1);
						currentAngle1 += angleDelta1;
						leftBuffer[sample] = currentSample * level;
						rightBuffer[sample] = currentSample * level;
					}
					else {
						auto currentSample = (float)std::sin(currentAngle2);
						currentAngle2 += angleDelta2;
						leftBuffer[sample] = currentSample * level;
						rightBuffer[sample] = currentSample * level;
					}
					sample++;
				}
				sampleAEcrire = 0;
			}
			else {
				sampleAEcrire -= bufferToFill.numSamples;
				for (int i = 0; i < bufferToFill.numSamples; i++) {
					updateAngleMetro();
					if (noteJouee == 0) {
						auto currentSample = (float)std::sin(currentAngle1);
						currentAngle1 += angleDelta1;
						leftBuffer[sample] = currentSample * level;
						rightBuffer[sample] = currentSample * level;
					}
					else {
						auto currentSample = (float)std::sin(currentAngle2);
						currentAngle2 += angleDelta2;
						leftBuffer[sample] = currentSample * level;
						rightBuffer[sample] = currentSample * level;
					}
					sample++;
				}

			}
		}
		else if (nbBlocASauter == 0) {
			std::cout << "initson" << std::endl;
			noteJouee = (noteJouee + 1) % Numerateur;

			for (int i = 0; i < SampleAPasser; i++) {
				updateAngleMetro();
				leftBuffer[sample] = 0;
				rightBuffer[sample] = 0;
				sample++;
			}



			int BLOCKSIZE = bufferToFill.numSamples;
			int passBlocTmp = sampleParTemps - (BLOCKSIZE - sample); //BLOCSIZE
			nbBlocASauter = passBlocTmp / BLOCKSIZE;
			SampleAPasser = passBlocTmp % BLOCKSIZE;
			sampleAEcrire = dureeSonSample;

			if (aller == 0) {
				angleMetro = angleMin;
				aller = 1;
			}
			else {
				angleMetro = angleMax;
				aller = 0;
			}

			if (sampleAEcrire < (BLOCKSIZE - sample)) {
				for (int i = 0; i < sampleAEcrire; i++) {
					updateAngleMetro();
					if (noteJouee == 0) {
						auto currentSample = (float)std::sin(currentAngle1);
						currentAngle1 += angleDelta1;
						leftBuffer[sample] = currentSample * level;
						rightBuffer[sample] = currentSample * level;
					}
					else {
						auto currentSample = (float)std::sin(currentAngle2);
						currentAngle2 += angleDelta2;
						leftBuffer[sample] = currentSample * level;
						rightBuffer[sample] = currentSample * level;
					}

					//BALANCELESON
				}
				sampleAEcrire = 0;
			}
			else {
				sampleAEcrire -= (BLOCKSIZE - sample);
				for (int i = 0; i < bufferToFill.numSamples; ++i) {
					updateAngleMetro();
					if (noteJouee == 0) {
						auto currentSample = (float)std::sin(currentAngle1);
						currentAngle1 += angleDelta1;
						leftBuffer[sample] = currentSample * level;
						rightBuffer[sample] = currentSample * level;
					}
					else {
						auto currentSample = (float)std::sin(currentAngle2);
						currentAngle2 += angleDelta2;
						leftBuffer[sample] = currentSample * level;
						rightBuffer[sample] = currentSample * level;
					}
					//BALANCELESON
				}
			}

		}
		return;
	}

	//////////////////////////////////////////
	//AUDIO WITH SAMPLES
	//
	////////////////////////////////////////////
	void openButtonUpClicked()
	{
		chooser = std::make_unique<juce::FileChooser>("Choisis son en Wav pour le debut de mesure mon reuf",
			juce::File{},
			"*.wav");
		auto chooserFlags = juce::FileBrowserComponent::openMode
			| juce::FileBrowserComponent::canSelectFiles;

		chooser->launchAsync(chooserFlags, [this](const FileChooser& fc)
		{
			auto file = fc.getResult();

			if (file != File{})
			{
				auto* reader = formatManager.createReaderFor(file);

				if (reader != nullptr)
				{
					auto newSource = std::make_unique<juce::AudioFormatReaderSource>(reader, true);
					transportSource.setSource(newSource.get(), 0, nullptr, reader->sampleRate);
					readerSource.reset(newSource.release());
				}
			}
		});
	}

	void openButtonDownClicked()
	{
		chooser = std::make_unique<juce::FileChooser>("Choisis un son en Wav pour le milieu de mesure mon reuf",
			juce::File{},
			"*.wav");
		auto chooserFlags = juce::FileBrowserComponent::openMode
			| juce::FileBrowserComponent::canSelectFiles;

		chooser->launchAsync(chooserFlags, [this](const FileChooser& fc)
		{
			auto file = fc.getResult();

			if (file != File{})
			{
				auto* reader = formatManager.createReaderFor(file);

				if (reader != nullptr)
				{
					auto newSource = std::make_unique<juce::AudioFormatReaderSource>(reader, true);
					transportSource.setSource(newSource.get(), 0, nullptr, reader->sampleRate);
					readerSource2.reset(newSource.release());
				}
			}
		});
	}
/// <summary>
/// /////////////////////////////////////////////
/// </summary>
	void playsoundsample(const juce::AudioSourceChannelInfo& bufferToFill) 
	{
		if (readerSource.get() == nullptr)
		{
			bufferToFill.clearActiveBufferRegion();
			return;
		}

		transportSource.getNextAudioBlock(bufferToFill);
		return;
	}
private:
	SceneComponent scene;
    int nbBlocASauter=0;
    int Numerateur=4;
    int noteJouee=3;
	
    int d = 3;
   
    std::map<int, int> denomDic = { {1,240},
                          {2,120},
                          {3,60},
                          {4,30},
                          {5,15} };
    int sampleParTemps;
    int BPM=100;
    int sampleAEcrire=0;
    int SampleAPasser=0;

    double frequency1= 440.0;
    double frequency2= 329.63;

    int dureeSonSample = 4410;
    int play = 0;

    juce::Slider BPMSlider;
    juce::Slider numerateurSlider;
    juce::ComboBox denominateur;
    juce::TextButton lancement;
    juce::Slider NoteUp;
    juce::Slider NoteDown;
    juce::Slider Level;

    juce::TextButton openButtonUp;
    juce::TextButton openButtonDown;
	juce::ComboBox byAudio;
    
    int aller = 0;
    double angleMax = 3*juce::MathConstants<double>::pi/4;
	double angleMetro = angleMax;
    double angleMin = juce::MathConstants<double>::pi / 4;
    
    double level = 0.15;
    double currentSampleRate = 0.0, currentAngle1 = 0.0,currentAngle2=0.0, angleDelta1 = 0.0, angleDelta2 = 0.0; // [1]

	//=======================================
	//FILE OPENER GESTION
	//
	//=======================================
	std::unique_ptr<juce::FileChooser> chooser;

	juce::AudioFormatManager formatManager;
	std::unique_ptr<juce::AudioFormatReaderSource> readerSource;
	std::unique_ptr<juce::AudioFormatReaderSource> readerSource2;
	juce::AudioTransportSource transportSource;
	juce::ToggleButton AudioSample;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};
