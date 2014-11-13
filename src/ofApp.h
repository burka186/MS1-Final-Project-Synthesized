#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    //--------------------------------------------------------
    
    //sound
    
    void audioOut(float * input, int bufferSize, int nChannels);
    
    ofSoundStream soundStream;
    
    float pan;
    int sampleRate;
    float volume;
    
    vector <float> lAudio;
    vector <float> rAudio;
    
    float 	targetFrequency;
    float 	phase;
    float 	phaseAdder;
    float 	phaseAdderTarget;
    
    //--------------------------------------------------------
    
    //arduino
    ofArduino	ard;
    bool		bSetupArduino;			// flag variable for setting up arduino once
    
    private:
    
        void setupArduino(const int & version);
        void analogPinChanged(const int & pinNum);
        void updateArduino();
    
        int ardReading;
        string potValue;
		
};
