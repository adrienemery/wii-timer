#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

    // OF Stuff
    ofEnableAlphaBlending();
    ofSetVerticalSync(true);
    ofSetFrameRate(100);
    
    // Initialize OSC
    receiver.setup(PORT);
    
    // Initialize UI
    gui = new ofxUICanvas(20, 20, ofGetWidth()-40, ofGetHeight()-40);
    timeLabel = new ofxUILabel(ofGetWidth()/2 - 70, ofGetHeight()/2 -50 , 100, "0.00", OFX_UI_FONT_LARGE);
    button = new ofxUILabelButton(ofGetWidth()/2 - 120, ofGetHeight()/2 + 20, 200, false, "ENABLE");
    
    gui->addWidget(timeLabel);
    gui->addWidget(button);
    
    gui->loadSettings("GUI/guiSettings.xml");
    ofAddListener(gui->newGUIEvent, this, &testApp::guiEvent);

    
    // Initialize control variables
    enabled = false;
    running = false;
    startTime = 0;
    stopTime = 0;
    time = 0;
    
    
}

//--------------------------------------------------------------
void testApp::update(){
    
    // update the color of the button
    button->setDrawFill(true);
    if(button->getName() == "ENABLE"){
        button->setColorFill(ofColor(34,139,34));
    }else{
        button->setColorFill(ofColor(255,0,0));
    }
    
    // check for data from Osculator
    while(receiver.hasWaitingMessages()){
        
        if(m.getAddress() == ADDRESS && m.getArgAsFloat(0) == 0 && !running && enabled){
            startTime = ofGetElapsedTimeMillis();
            running = true;
            
        }else if(m.getAddress() == ADDRESS && m.getArgAsFloat(0) == 0 && running && enabled){
            
            // this check ensures that the person has entirely gone by the sensor and thier trailing leg doesn't trip the sensor 
            if(ofGetElapsedTimeMillis() - startTime > 400){
                stopTime = ofGetElapsedTimeMillis();        
                time = (stopTime - startTime) / 1000.0;     // get time in seconds
                running = false;
                enabled = false;
            }
        }
    }
    
    // update the time displayed 
    if(running){
        timeLabel->setLabel(ofToString((ofGetElapsedTimeMillis()-startTime)/1000).substr(0,4));
    }else{
        timeLabel->setLabel(ofToString(time).substr(0,4));
    }


}

//--------------------------------------------------------------
void testApp::draw(){
    
    // draw background color
    ofBackground(0);

}
//--------------------------------------------------------------
void testApp::guiEvent(ofxUIEventArgs &e){

    // handle button click events
    if(e.widget->getID() == button->getID() && button->getValue()){
        
        if(button->getName() == "ENABLE"){
            enabled = true;
            button->setName("RESET");
            button->setLabelText("RESET");
        }else{
            
            if(running){
                time = 0.00;
                running = false;
                enabled = false;
                button->setLabelText("ENABLE");
                button->setName("ENABLE");

            }else{
                enabled = false;
                button->setLabelText("ENABLE");
                button->setName("ENABLE");
                time = 0.00;
            }
        }
        
    }

}
void testApp::exit(){
    
    gui->saveSettings("GUI/guiSettings.xml");
    delete gui;
    
}
//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
    // use RETURN key for testing if no wiimote connected
    
    if(key == OF_KEY_RETURN && !running && enabled){
        startTime = ofGetElapsedTimeMillis();
        running = true;
        
    }else if(key == OF_KEY_RETURN && running && enabled){
       
        // this check ensures that the person has entirely gone by the sensor and thier trailing leg doesn't trip the sensor
        if(ofGetElapsedTimeMillis() - startTime > 400){
            stopTime = ofGetElapsedTimeMillis();
            time = (stopTime - startTime) / 1000.0;     // get time in seconds
            running = false;
            enabled = false;
        }
        
    }
    
    
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}