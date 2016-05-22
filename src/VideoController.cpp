//
//  VideoController.cpp
//  LedStripPlayer
//
//  Created by PleekMan on 14/5/2016.
//
//

#include "VideoController.h"


void VideoController::initialize(string videoPath, string videoName, int _keyFrames[], int totalKeys, ofFbo *_renderSurface){
    
    video.loadMovie(videoPath + videoName);
    video.setLoopState(OF_LOOP_NONE);
    video.play();
    video.setPaused(true);
    
    cout << totalKeys<< " - " << sizeof(*_keyFrames) << endl;
    
    description = videoName;
    
    //LOAD KEYFRAME DATA
    for (int i=0; i< totalKeys; i++) {
        KeyFrame newKeyFrame;
        newKeyFrame.frame = _keyFrames[i];
        newKeyFrame.name = ofToString(newKeyFrame.frame);
        keyFrames.push_back(newKeyFrame);
    }
    
    // LOAD KEYFRAME THUMBNAILS
    string thumbsDir = videoPath + "thumbs/";
    for (int i=0; ofDirectory::doesDirectoryExist(thumbsDir + ofToString(i) + ".png"); i++) {
            ofImage newImage;
            newImage.loadImage(thumbsDir + ofToString(i) + ".png");
            keyThumbs.push_back(newImage);
    }


    
    atKeyFrame = keyFrames[0].frame;
    setInOutFrames(atKeyFrame,keyFrames[atKeyFrame + 1].frame); // WATCH OUT FOR LAST KEYFRAMES
    
    totalFrames = video.getTotalNumFrames();
    
    sectionLoop = false;
    isActive = false;
    isSelected = false;
    
    renderSurface = _renderSurface;
    
    position = ofVec2f();
    size = ofVec2f();
    
}

void VideoController::update(){
    
    if (isActive) {
        
        if (getCurrentFrame() >= outFrame - 1) {
            if (sectionLoop) {
                jumpBack();
            } else {
                updateKeyFrames(atKeyFrame + 1);
            }
        }

        
        // DRAW TO PIXEL SAMPLING FBO
        renderSurface->begin();
        
        video.update();
        video.draw(0,0);
        
        
        renderSurface->end();
    
    }
    
    
}

void VideoController::render(){
    
    
    float videoFrame = getCurrentFrame();
    float playHeadPos = videoFrame / totalFrames;
    //cout << "Frame: " << videoFrame <<  endl;
    
    // SOME GUI SHIT
    
    // TIMELINE BACKGROUND
    if (isActive) {
        ofFill();
        ofSetColor(70,70,70);
        ofRect(0, position.y - 30, 1030, 75);
    }
    if (isSelected) {
        ofNoFill();
        ofSetColor(232, 70, 80);
        ofLine(0, position.y - 30, 1030, position.y - 30);
        ofLine(0, position.y + 45, 1030, position.y + 45);
    }
    
    // TIMELINE PROGRESS BAR
    ofFill();
    if(isActive){
        ofSetColor(10,180,190);
    } else{
        ofSetColor(0,100,100);
    }
    ofRect(position, size.x, size.y);
    

    
    // NAME + ID
    ofSetColor(10,130, 140);
    ofRect(position.x, position.y, -20, size.y);
    ofSetColor(255);
    ofDrawBitmapString(description, ofPoint(position.x + 20, position.y + size.y - 3));
    ofDrawBitmapString(ofToString(ID), ofPoint(position.x - 15, position.y + size.y - 3));
    
    
    // DRAW KEYFRAMES
    for (int i=0; i<keyFrames.size(); i++) {
        float x= position.x + ((keyFrames[i].frame / (float)totalFrames) * size.x);
        float y = position.y - 3;
        
        if (atKeyFrame == i) {
            ofSetColor(230, 70, 80);
        } else {
            ofSetColor(30, 120, 190);
        }
        ofFill();
        ofRect(x, y - 15, 20, 15);

        ofSetColor(255);
        ofLine(x, position.y  + size.y, x, y - 15);
        
        ofDrawBitmapString(ofToString(i), x + 3, y - 3);
    }
    
    // PLAYHEAD BAR
    //ofNoFill();
    ofSetColor(230, 70, 80);
    ofSetLineWidth(3);
    float headX = position.x + (playHeadPos * size.x);
    ofLine(headX, position.y + size.y, headX, position.y - 18);
    ofSetLineWidth(1);
    ofRect(headX, position.y - 3, 15, 3);
    
    ofSetColor(255);
    ofDrawBitmapString(ofToString(atKeyFrame), headX + 3, position.y - 6);

    ofDrawBitmapString(ofToString(videoFrame), headX + 3, position.y + size.y - 3);
    
    
    if (sectionLoop){
        ofSetColor(230, 70, 80);
        ofRect(position.x, position.y + size.y, 80, 18);
        ofSetColor(255);
        ofDrawBitmapString("LOOPING", position.x + 5, position.y + size.y + 14);
    }
    
    
    
}

void VideoController::updateKeyFrames(int keyFrame){
    
    // IF VIDEO REACHED THE END
    if (getCurrentFrame() >= getTotalFrames() - 1) {
    //if (getCurrentFrame() >= 5) {
        video.setPaused(true);
        video.setFrame(getTotalFrames() - 1);
    } else {
        atKeyFrame = keyFrame;
        setInOutFrames(keyFrames[atKeyFrame].frame, keyFrames[atKeyFrame + 1].frame);
    }

}

void VideoController::jumpToNextKeyFrame(){
    if(atKeyFrame + 2 < keyFrames.size()){ // + 2, CUZ THE LAST FRAME OF THE VIDEO IS CONSIDERED A KEYFRAME
        atKeyFrame += 1;
        setInOutFrames(keyFrames[atKeyFrame].frame, keyFrames[atKeyFrame + 1].frame);
        video.setFrame(inFrame);
        video.play();
    }
}

void VideoController::jumpToPreviousKeyFrame(){
    if (atKeyFrame != 0) {
        atKeyFrame -= 1;
        setInOutFrames(keyFrames[atKeyFrame].frame, keyFrames[atKeyFrame + 1].frame);
        video.setFrame(inFrame);
        video.play();
    }
}

void VideoController::jumpBack(){
    setInOutFrames(keyFrames[atKeyFrame].frame, keyFrames[atKeyFrame + 1].frame);
    video.setFrame(inFrame);
    video.play();
    
}

void VideoController::setInOutFrames(int _inFrame, int _outFrame){
    inFrame = _inFrame;
    outFrame= _outFrame;
}

void VideoController::toggleLoopSection(){
    sectionLoop = !sectionLoop;
}


int VideoController::getCurrentFrame(){
    return video.getCurrentFrame();
}


int VideoController::getTotalFrames(){
    return video.getTotalNumFrames();
}

void VideoController::setPosition(float _x, float _y){
    position.set(_x, _y);
}

void VideoController::setSize(float width, float height){
    size.set(width, height);
}

void VideoController::setID(int _ID){
    ID = _ID;
}

void VideoController::setActive(bool state){
    isActive = state;
    if (isActive) {
        video.setPaused(false);
        video.play();
    } else {
        video.setPaused(true);
    }
}

void VideoController::setSelected(bool state){
    isSelected = state;
}

bool VideoController::setKeyFrameSelection(){
    
    for (int i=0; i<keyFrames.size() - 1; i++) {
        float keyX = position.x + ((keyFrames[i].frame / (float)totalFrames) * size.x);
        float nextKeyX = position.x + ((keyFrames[i + 1].frame / (float)totalFrames) * size.x);
        ofRectangle keyArea = ofRectangle(keyX, position.y, nextKeyX - keyX, size.y);
        
        if (keyArea.inside(ofGetMouseX(), ofGetMouseY())) {
            updateKeyFrames(i);
            video.setFrame(inFrame);
            isSelected = true;
            cout << "KeyFrame: " << i << " || IN: " << inFrame << " || OUT: " << outFrame << " || videoFrame: " << getCurrentFrame() << endl;
            return true;
            break;
        }
    }
    return false;
    
}

int VideoController::checkKeyFrameSelection(){
    
    int keySelected = -1;
    
    for (int i=0; i<keyFrames.size() - 1; i++) {
        float keyX = position.x + ((keyFrames[i].frame / (float)totalFrames) * size.x);
        float nextKeyX = position.x + ((keyFrames[i + 1].frame / (float)totalFrames) * size.x);
        ofRectangle keyArea = ofRectangle(keyX, position.y, nextKeyX - keyX, size.y);
        
            if (keyArea.inside(ofGetMouseX(), ofGetMouseY())) {
                keySelected = i;
                break;
            }
    }
    
    return keySelected;
}

ofImage* VideoController::getThumbForKey(int i){
    return &keyThumbs[i];
}

ofImage* VideoController::getThumbForActiveKey(){
    return &keyThumbs[atKeyFrame];
}




