#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxUI.h"
#include "ofxXmlSettings.h"

#define HOST "localhost" 
#define PORT 8000        // this should be the output port in Osculator
#define ADDRESS "/wii/2/ir/xys/1/2" // this must match the correct address for the ir size value in Oscluator

class testApp : public ofBaseApp{

	
public:
    void setup();
    void update();
    void draw();

    void keyPressed  (int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    void guiEvent(ofxUIEventArgs &e);
    void exit();
    
    // OSC
    ofxOscReceiver receiver;
    ofxOscMessage  m;
    
    // UI
    ofxUICanvas*        gui;
    ofxUILabelButton*   button;
    ofxUILabel*         timeLabel;
    
    // Control variables
    bool enabled;
    bool running;
    
    float startTime;
    float stopTime;
    float time;
    
    
    
    
		
};
