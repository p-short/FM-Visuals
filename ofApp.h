#pragma once

#include "ofMain.h"
#include "ofxMaxim.h"
#include "Walker.hpp"

class ofApp : public ofBaseApp{
    
public:
    void setup() override;
    void update() override;
    void draw() override;
    
    void keyPressed(int key) override;
    void keyReleased(int key) override;
    void mouseMoved(int x, int y) override;
    void mouseDragged(int x, int y, int button) override;
    void mousePressed(int x, int y, int button) override;
    void mouseReleased(int x, int y, int button) override;
    void mouseEntered(int x, int y) override;
    void mouseExited(int x, int y) override;
    void windowResized(int w, int h) override;
    void dragEvent(ofDragInfo dragInfo) override;
    void gotMessage(ofMessage msg) override;
    
    //sound objects
    ofSoundStream mySoundStream;
    void audioOut(ofSoundBuffer& output) override;
    
    //maxi sound objects
    maxiEnv env;
    maxiOsc mySaw, myLFO, osc1, osc2, osc3, osc4;
    
    //variables used in ofApp.cpp
    int trig { 0 }, freq { 440 };
    float greenCount, blueCount;
    std::vector<float> myVector;
    float blue, green;
    std::vector <unique_ptr <Walker>> walkers;
    bool showText { true };
};
