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
    
    if(isSelected){
        ofSetColor(70, 70, 0);
        ofFill();
    } else{
        ofNoFill();
        ofSetColor(20, 20, 0);
    }
    ofRect(position, size.x, size.y);
    
    // PLAYHEAD BAR
    ofNoFill();
    ofSetColor(255, 255, 0);
    ofLine(position.x + (playHeadPos * size.x), position.y - 5, position.x + (playHeadPos * size.x), position.y + size.y + 5);
    ofDrawBitmapString(ofToString(videoFrame), position.x + (playHeadPos * size.x), position.y - 20);
    ofDrawBitmapString(ofToString(atKeyFrame), position.x + (playHeadPos * size.x), position.y - 40);

    ofSetColor(0, 255, 0);
    for (int i=0; i<keyFrames.size(); i++) {
        float x= position.x + ((keyFrames[i].frame / (float)totalFrames) * size.x);
        ofLine(x, position.y - 5, x, position.y + size.y + 5);
        ofDrawBitmapString(ofToString(i), x, position.y + size.y);
    }
    
    if (sectionLoop)ofDrawBitmapString("LOOPING", position.x , position.y - 10);
    
    
    
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




