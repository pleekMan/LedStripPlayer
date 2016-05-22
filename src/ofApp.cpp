#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    settings.load("settings.xml");
    
    videoManager.initialize(&settings);
    sampler.initialize(&settings);
    sampler.setSamplingSurface(&videoManager.renderSurface);
    ledStripController.setup();
    
    backgroundImage.loadImage("gui/Fondo.png");
}




//--------------------------------------------------------------
void ofApp::update(){
    
    
    videoManager.update();
    sampler.update();
    
    
    ledStripController.update();
    for (int i=0; i < sampler.getLedStripCount(); i++) {
        vector<ofColor> cols = sampler.sampleLedStrip(i);
        ledStripController.setLedStrip(i, cols);
    }
    
}



//--------------------------------------------------------------
void ofApp::draw(){
    ofClear(50);
    backgroundImage.draw(0,0);
    
    
    videoManager.render();
    sampler.render();
    
    showMouseCoordinates();

    

}

void ofApp::showMouseCoordinates(){
    int xOffset = ofGetMouseX() < ofGetWidth() * 0.5 ? 10 : -120;
    int yOffset = ofGetMouseY() < ofGetHeight() * 0.5 ? 10 : -10;
    ofPushStyle();
    ofSetColor(255, 0, 0);
    ofFill();
    ofDrawBitmapString("x" + ofToString(ofGetMouseX()) + " :: y" + ofToString(ofGetMouseY()), ofGetMouseX() + xOffset, ofGetMouseY() + yOffset);
    ofPopStyle();
    
}





//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if (key == 'q') {
        videoManager.jumpToPreviousKeyFrame();
    }
    if (key == 'w') {
        videoManager.jumpBack();
    }
    if (key == 'e') {
        videoManager.jumpToNextKeyFrame();
    }
    
    if (key == 'l') {
        videoManager.toggleLoopSection();
    }
    
    if (key == 'a') {
        videoManager.switchToPreviousVideo();
    }
    if (key == 's') {
        videoManager.switchToNextVideo();
    }
    
    if(key == ' '){
        videoManager.keyPressed(key);
    }

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    videoManager.mouseDragged(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
    videoManager.mousePressed(x,y,button);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

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
