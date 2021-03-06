#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    settings.load("settings.xml");
    
    videoManager.initialize(&settings);
    sampler.initialize(&settings);
    sampler.setSamplingSurface(&videoManager.renderSurface);
}




//--------------------------------------------------------------
void ofApp::update(){
    videoManager.update();
    sampler.update();
}



//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(50);
    
    
    //ofPushMatrix();
    //ofTranslate(100, 100);
    
    videoManager.render();
    sampler.render();

    //ofPopMatrix();
}







//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if (key == 'q') {
        videoManager.jumpToPreviousKeyFrame();
    }
    if (key == 'w') {
        videoManager.jumpToNextKeyFrame();
    }
    
    if (key == 'l') {
        videoManager.toggleLoopSection();
    }
    
    if(key == 's'){
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

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

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
