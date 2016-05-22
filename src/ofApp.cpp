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
    ofPushStyle();
    ofSetColor(255, 0, 0);
    ofFill();
    
    ofDrawBitmapString("x" + ofToString(ofGetMouseX()) + " :: y" + ofToString(ofGetMouseY()), ofGetMouseX() - 100, ofGetMouseY() - 5);
    
    
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
        
        videoManager.trigger();
        //unsigned char *ledColor =  sampler.sampleLedStrip(0);
        
        // FIRST PIXEL OF FIRST LED
        //cout << ledColor[0] << " - " << ledColor[1] << " - " << ledColor[2] << endl;
        
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
