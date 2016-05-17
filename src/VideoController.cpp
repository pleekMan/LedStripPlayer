//
//  VideoController.cpp
//  LedStripPlayer
//
//  Created by PleekMan on 14/5/2016.
//
//

#include "VideoController.h"


void VideoController::initialize(string videoPath, int _keyFrames[], int totalKeys, ofFbo *_renderSurface){
    
    videoMain.loadMovie(videoPath);
    videoMain.setLoopState(OF_LOOP_NORMAL);
    videoMain.play();
    videoMain.setPaused(true);
    
    cout << totalKeys<< " - " << sizeof(*_keyFrames) << endl;
    
    
    for (int i=0; i< totalKeys; i++) {
        KeyFrame newKeyFrame;
        newKeyFrame.frame = _keyFrames[i];
        newKeyFrame.name = ofToString(newKeyFrame.frame);
        keyFrames.push_back(newKeyFrame);
    }
    
    atKeyFrame = keyFrames[0].frame;
    setInOutFrames(atKeyFrame,keyFrames[atKeyFrame + 1].frame); // WATCH OUT FOR LAST KEYFRAMES
    
    totalFrames = videoMain.getTotalNumFrames();
    
    sectionLoop = false;
    isActive = false;
    
    renderSurface = _renderSurface;
    
    position = ofVec2f();
    size = ofVec2f();
    
}

void VideoController::update(){
    
    if (isActive) {
        
        if (getCurrentFrame() >= outFrame) {
            if (sectionLoop) {
                //updateKeyFrames(atKeyFrame);
                jumpBack();
            } else {
                updateKeyFrames(atKeyFrame + 1);
            }
        }
        
        renderSurface->begin();
        
        videoMain.update();
        videoMain.draw(0,0);
        
        
        renderSurface->end();
    
    }
    
    
}

void VideoController::render(){
    
    
    float videoFrame = getCurrentFrame();
    float playHeadPos = videoFrame / totalFrames;
    //float videoTotalFrames = videoMain.getTotalNumFrames();
    
    // PLAYHEAD BAR
    ofNoFill();
    ofSetColor(255, 0, 0);
    ofLine(position.x + (playHeadPos * size.x), position.y - 5, position.x + (playHeadPos * size.x), position.y + size.y + 5);
    ofDrawBitmapString(ofToString(videoFrame), position.x + (playHeadPos * size.x), position.y - 20);
    ofDrawBitmapString(ofToString(atKeyFrame), position.x + (playHeadPos * size.x), position.y - 40);

    ofSetColor(0, 255, 0);
    for (int i=0; i<keyFrames.size(); i++) {
        float x= position.x + ((keyFrames[i].frame / (float)totalFrames) * size.x);
        ofLine(x, position.y - 5, x, position.y + size.y + 5);
        ofDrawBitmapString(ofToString(i), x, position.y + size.y);
    }
    
    if (sectionLoop) {
        ofDrawBitmapString("LOOPING", 0, -60);
    }
    
    // SOME GUI SHIT
    ofNoFill();
    ofSetColor(127, 0, 127);
    ofRect(position, size.x, size.y);
}

void VideoController::updateKeyFrames(int keyFrame){
    atKeyFrame = atKeyFrame >= keyFrames.size() - 1 ? 0 : keyFrame;
    setInOutFrames(keyFrames[atKeyFrame].frame, keyFrames[atKeyFrame + 1].frame);

}

void VideoController::jumpToNextKeyFrame(){
    atKeyFrame = atKeyFrame >= keyFrames.size() - 1 ? 0 : atKeyFrame += 1;
    setInOutFrames(keyFrames[atKeyFrame].frame, keyFrames[atKeyFrame + 1].frame);
    videoMain.setFrame(inFrame);
    /*
     if (atKeyFrame >= keyFrames.size() - 1) {
     atKeyFrame = 0;
     } else {
     atKeyFrame += 1;
     }
     */

}

void VideoController::jumpToPreviousKeyFrame(){
    atKeyFrame = atKeyFrame <= 0 ? keyFrames.size() - 2 : atKeyFrame -= 1;
    setInOutFrames(keyFrames[atKeyFrame].frame, keyFrames[atKeyFrame + 1].frame);
    videoMain.setFrame(inFrame);

}

void VideoController::jumpBack(){
    //atKeyFrame = atKeyFrame <= 0 ? keyFrames.size() - 2 : atKeyFrame -= 1;
    setInOutFrames(keyFrames[atKeyFrame].frame, keyFrames[atKeyFrame + 1].frame);
    videoMain.setFrame(inFrame);
    
}

void VideoController::setInOutFrames(int _inFrame, int _outFrame){
    inFrame = _inFrame;
    outFrame= _outFrame;
}

void VideoController::toggleLoopSection(){
    sectionLoop = !sectionLoop;
}


int VideoController::getCurrentFrame(){
    return videoMain.getCurrentFrame();
}


int VideoController::getTotalFrames(){
    return videoMain.getTotalNumFrames();
}

void VideoController::setPosition(float _x, float _y){
    position.set(_x, _y);
}

void VideoController::setSize(float width, float height){
    size.set(width, height);
}

void VideoController::setActive(bool state){
    isActive = state;
    if (isActive) {
        videoMain.setPaused(false);
        videoMain.play();
    } else {
        videoMain.setPaused(true);
    }
}


