#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    //sound setup
    int sampleRate = 44100;
    int bufferSize = 512;
    
    ofxMaxiSettings::setup(sampleRate, 2, bufferSize);
    
    ofSoundStreamSettings settings;
    settings.setOutListener(this);
    settings.sampleRate = sampleRate;
    settings.numOutputChannels = 2;
    settings.numInputChannels = 0;
    settings.bufferSize = bufferSize;
    mySoundStream.setup(settings);
    
    //setting up the ADSR values of a maxi envelope
    env.setAttack(1000);
    env.setDecay(400);
    env.setSustain(1);
    env.setRelease(3500);
    
    //init these variables to something random
    greenCount = ofRandom(0.5);
    blueCount = ofRandom(0.5);
    
    //loop through every pixel left to right mapping that range to 0 - two pi and store it in a vector.
    for (int i = 0; i < ofGetWidth(); i++)
    {
        float mappedValues = ofMap(i, 0, ofGetWidth(), 0, M_PI * 2);
        myVector.push_back(mappedValues);
    }
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

    //loop through vector of mapped values
    for (int i = 0; i < myVector.size(); i++)
    {
        //use mapped values and pass them to noise function multiplying them by 255, this creates a pattern in red across the canvas, noise is also used in the green channel only this time its value is inremented by green count changing the green channel over time. same with the blue channle only it uses a sin function. The idea is that this creates a pleasing background that changes over time
        ofSetColor(ofNoise(myVector[i]) * 255, green * 125, blue * 255);
        ofDrawLine(i, 0, i, ofGetHeight());
    }
    
    //use values to change background color
    blue = ofNoise(blueCount);
    green = ofMap(sin(greenCount),-1, 1, 0, 1);
    blueCount += 0.004;
    greenCount += 0.01;
    
    //draw walkers to canvas.
    for(int i = 0; i < walkers.size(); i++)
    {
        //while walker is in bounds of canvas do this
        if (!walkers[i]->isOut()) {
             walkers[i]->velocity();
             walkers[i]->move();
             walkers[i]->update();
             walkers[i]->draw();
             walkers[i]->reduceLifeSpan();
         }
        //draw untill walker is out of bounds or life = 0
         else if (walkers[i]->isOut() || walkers[i]->lifeSpan())
         {
             walkers[i]->draw();
             walkers[i]->reduceLifeSpan();
         }
        //once life is 0 clear posVec vector
         else if (!walkers[i]->lifeSpan())
         {
             walkers[i]->emptyPosVec();
         }
    }
    //display text so the user knows what to do.
    if (showText)
    {
        ofSetColor(0);
        ofDrawBitmapString("Click me", (ofGetWidth() / 2) - 10, ofGetHeight() / 2);
    }
}

//----------------------------------------------------------
void ofApp::audioOut(ofSoundBuffer &output)
{
    //loop through buffer and write into it
    std::size_t outChans = output.getNumChannels();
    for (int i = 0; i < output.getNumFrames(); ++i)
    {
        //using the blue and green values from drawing the background to modulate the frequency of a sinewave, there is a clear harmonic relationship between the values selected, so its rich in harmonic content and not inharmonic an dischordant.
        float fmFun = osc1.sinewave(((osc2.sinewave(blue * 0.1) *
                              660) * osc3.sinewave(110) *
                              osc4.sinewave(green * 0.01) * 6.875)) * 0.5;
        
        //modulating a saws fequency with a sine for a darker my erie sound.
        //sawTooth is then passed through the adsr function and asigned to sawEnv.
        //the saws frequency / sawEnv trigger is determed in the mousePressed function.
        float sawTooth = mySaw.saw(freq + (myLFO.sinewave(0.9) * 5)) * 0.4;
        
        float sawEnv = env.adsr(sawTooth, trig);

        //output sound
        output[i * outChans] = fmFun + sawEnv;
        output[i * outChans + 1] = output[i * outChans];
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
    showText = false; // once clicked no longer display text to canvas
    //use floor to round down a random floating point between 0 - 7 to be an int.
    int randVal = floor(ofRandom(7));
    //randVal is then used in switch statment to pick what frequencey sawTooth should play at
    switch(randVal)
    {
        case 0 :
            freq = 440;
            break;
        case 1 :
            freq = 493.88;
            break;
        case 2 :
            freq = 523.25;
            break;
        case 3 :
            freq = 587.33;
            break;
        case 4 :
            freq = 659.26;
            break;
        case 5 :
            freq = 698.46;
            break;
        case 6 :
            freq = 783.99;
            break;
    }
    //when mouse pressed trigger envelope
    trig = 1;
    //when mouse pressed push walkers in to walkers vector (these are then drawn in draw)
    for (int i = 0; i < 10; i++)
    {
        auto w = std::make_unique<Walker>(ofGetMouseX(),ofGetMouseY());
        walkers.push_back(std::move(w));
    }
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    //when mouse released trigger envelope off
    trig = 0;
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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
