#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    
    ofBackground(0);
    
    //SOUND STUFF HERE -----------------------------
    
    int bufferSize		= 512;
    sampleRate 			= 44100;
    phase 				= 0;
    phaseAdder 			= 0.0f;
    phaseAdderTarget 	= 0.0f;
    volume				= 0.5f;
    //bNoise 				= false;
    
    lAudio.assign(bufferSize, 0.0);
    rAudio.assign(bufferSize, 0.0);
    
    soundStream.setup(this, 2, 0, sampleRate, bufferSize, 4);
    
    //ARDUINO STUFF HERE ---------------------------
    
    //connect to arduino
    ard.connect("/dev/tty.usbserial-DA00T1YT", 57600);
    
    //listen for arduino to be ready. when it is ready, call setupArduino() function
    ofAddListener(ard.EInitialized, this, &ofApp::setupArduino);
    bSetupArduino	= false;	// boolean flag so we setup arduino when it's ready
    
}

//--------------------------------------------------------------
void ofApp::update(){

    //pulls info from Arduino each frame
    updateArduino();
    
}

//--------------------------------------------------------------
void ofApp::setupArduino(const int & version) {
    
    // remove listener because we don't need it anymore
    ofRemoveListener(ard.EInitialized, this, &ofApp::setupArduino);
    
    //it is now safe to send commands to the arduino so set the boolean to true
    bSetupArduino = true;
    
    // print firmware name and version to the console
    ofLogNotice() << ard.getFirmwareName();
    ofLogNotice() << "firmata v" << ard.getMajorFirmwareVersion() << "." << ard.getMinorFirmwareVersion();
    
    //set pin A0 to analog input (this is the x axis of the accelerometer)
    ard.sendAnalogPinReporting(0, ARD_ANALOG);
    
    //listen for changes on the analog pin and call analogPinChanged()
    //function if there have been changes
    ofAddListener(ard.EAnalogPinChanged, this, &ofApp::analogPinChanged);
}

//--------------------------------------------------------------
//this is what gets called in the ofApp::update() function above
void ofApp::updateArduino() {
    
    // update the arduino, get any data or messages.
    // the call to ard.update() is required
    ard.update();

    // do not send anything until the arduino has been set up
    if (bSetupArduino) {
        //if the arduino is set up, get the analog data from pin 0
        ard.sendPwm(10, (ard.getAnalog(0)));
        
    }
    
}

//--------------------------------------------------------------
void ofApp::analogPinChanged(const int & pinNum) {
    // do something with the analog input. here we're simply going to print the pin number and
    // value to the screen each time it changes
    
    ardReading = ard.getAnalog(pinNum);
    
    potValue = "analog pin: " + ofToString(pinNum) + " = " + ofToString(ardReading);
    
    
}


//--------------------------------------------------------------
void ofApp::draw(){

    ofEnableAlphaBlending();
    ofSetColor(0, 0, 0, 127);
    ofRect(510, 15, 275, 150);
    ofDisableAlphaBlending();
    
    ofSetColor(255, 255, 255);
    if (!bSetupArduino){
        ofDrawBitmapString("arduino not ready...\n", 515, 40);
    } else {
        ofDrawBitmapString(potValue + "\n" +
                        "\nsending pwm: " + ofToString((int)(128 + 128 * sin(ofGetElapsedTimef()))), 515, 40);
    }
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------

void ofApp::audioOut(float * output, int bufferSize, int nChannels){
//    //pan = 0.5f;
//    float leftScale = 1 - pan;
//    float rightScale = pan;
//    
//    // sin (n) seems to have trouble when n is very large, so we
//    // keep phase in the range of 0-TWO_PI like this:
//    while (phase > TWO_PI){
//        phase -= TWO_PI;
//    }
    pan = 0.5f;
    float leftScale = 1 - pan;
    float rightScale = pan;
    
//    if (ardReading > 350 || ardReading < 300) {
        for (int i = 0; i < bufferSize; i++){
            lAudio[i] = output[i*nChannels    ] = ofRandom(0, 1) * volume * leftScale;
            rAudio[i] = output[i*nChannels + 1] = ofRandom(0, 1) * volume * rightScale;
        }
//    }
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
