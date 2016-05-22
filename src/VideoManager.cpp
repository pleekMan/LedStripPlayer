//
//  VideoManager.cpp
//  LedStripPlayer
//
//  Created by PleekMan on 14/5/2016.
//
//


#include "VideoManager.h"

ofVec2f VideoManager::renderSurfacePos;
ofVec2f VideoManager::renderSurfaceScale;

void VideoManager::initialize(ofXml *_settings){
    
    timelineScrollerY = 0;
    guiAnchor = ofVec2f(30,50);
    controllersSize = ofVec2f(1010 - 50,15);
    
    

    renderSurface.allocate(200, 100, GL_RGB);
    renderSurface.begin();
    ofClear(0);
    renderSurface.end();
    renderSurfacePos = ofVec2f(1375, 445);
    renderSurfaceScale = ofVec2f(1.4,1.3);
    
    //displayScale = ofVec2f(1.0);
    
    buildVideoControllers(_settings);
    activeVideo = 0;
    selectedVideo = 0;
    videoControllers[0].setActive(true);
    videoControllers[0].setSelected(true);
    
    thumbSelection = videoControllers[0].getThumbForKey(0);
    
}

void VideoManager::buildVideoControllers(ofXml *settings){
    
    settings->setTo("//videos"); // AT VIDEOS
    
    // GET VIDEO DATA - BEGIN ------------------
    int videoCount = settings->getNumChildren();
    cout << "VideoCount: " << ofToString(videoCount) << endl;
    settings->setToChild(0); // AT FIRST VIDEO
    
    for (int i=0; i<videoCount; i++) {
        VideoController newVideoController;
        
        string folderPath = settings->getAttribute("path");
        string videoName = settings->getAttribute("name");
        newVideoController.setID(i);

        cout << ofToString(i) << " -> Video Path: " << folderPath + videoName << endl;
        
        
        int keyCount = settings->getNumChildren();
        int keys[keyCount];
        
        settings->setToChild(0); // AT FIRST KEYFRAME
        for (int j=0; j<keyCount; j++) {
            keys[j] = settings->getValue<int>(""); // GET VALUE AT CURRENT NODE
            cout << ofToString(keys[j]) << endl;
            
            settings->setToSibling();
        }
        
        newVideoController.initialize(folderPath, videoName, keys, keyCount, &renderSurface);
        newVideoController.setSize(controllersSize.x, controllersSize.y);
        ofVec2f pos = ofVec2f(guiAnchor.x, guiAnchor.y + (i * (controllersSize.y + 60))); // EL +10 ES UN ESPACIO DE SEPARACION
        newVideoController.setPosition(pos.x, pos.y);
        
        videoControllers.push_back(newVideoController);
        
        settings->setToParent();
        
        settings->setToSibling();
    }
    
    // GET VIDEO DATA - END ------------------

    
    
    
    /*
    for (int i=0; i<1; i++) {
        VideoController newVideo;
        int keys[] = {0,170,184,354,536,706,875};
        
        newVideo.initialize("Aire y Niebla Test.mov", keys, sizeof(keys) / sizeof(*keys), &renderSurface);
        videoControllers.push_back(newVideo);
    }
     */
     
}

void VideoManager::update(){
    
    ofSetColor(255);
    for (int i=0; i<videoControllers.size(); i++) {
        videoControllers[i].update();
    }
    
}

void VideoManager::render(){
    
    // DRAW RENDER SURFACE SAMPLER & THUMB SELECTION
    ofPushMatrix();
    ofTranslate(renderSurfacePos.x, renderSurfacePos.y);
    ofScale(renderSurfaceScale.x, renderSurfaceScale.y);
        renderSurface.draw(0,0);
    ofPopMatrix();
    thumbSelection->draw(1065, 445, 280, 130);
    
    // RENDER GUI FOR EACH VIDEO
    ofSetColor(255);
    for (int i=0; i<videoControllers.size(); i++) {
        videoControllers[i].render();
    }
    
    
    // SOME GUI SHIT
    // TIMELINE SCROLLER
    ofNoFill();
    ofSetColor(140, 140, 200);
    ofRect(1030, 0, 15, ofGetHeight());
    ofFill();
    ofRect(ofPoint(1030,timelineScrollerY), 15, 15);
    
    
    /*
    ofNoFill();
    ofSetColor(0, 127, 127);
    ofRect(guiAnchor, 700,700);
    */
}

void VideoManager::jumpToNextKeyFrame(){
    videoControllers[activeVideo].jumpToNextKeyFrame();
}

void VideoManager::jumpToPreviousKeyFrame(){
    videoControllers[activeVideo].jumpToPreviousKeyFrame();
}
void VideoManager::jumpBack(){
    videoControllers[activeVideo].jumpBack();
}

void VideoManager::toggleLoopSection(){
    videoControllers[selectedVideo].toggleLoopSection();
}

void VideoManager::switchToNextVideo(){
    int nextVideo = activeVideo < videoControllers.size() ? activeVideo + 1 : activeVideo;
    switchToVideo(nextVideo);
}
void VideoManager::switchToPreviousVideo(){
    int prevVideo = activeVideo != 0 ? activeVideo - 1 : activeVideo;
    switchToVideo(prevVideo);

}

void VideoManager::switchToVideo(int videoNum){
    activeVideo = videoNum;
    for (int i = 0; i<videoControllers.size(); i++) {
        videoControllers[i].setActive(false);
    }
    videoControllers[activeVideo].setActive(true);
}

ofFbo VideoManager::getRenderSurface(){
    return renderSurface;
}

void VideoManager::selectVideo(int videoNum){
    for (int i=0; i < videoControllers.size(); i++) {
        videoControllers[i].setSelected(false);
    }
    videoControllers[videoNum].setSelected(true);
    selectedVideo = videoNum;
}

void VideoManager::trigger(){
    switchToVideo(selectedVideo);
}

void VideoManager::scrollTimeline(){
    guiAnchor.y = 30 + ofMap(ofGetMouseY(), 0, ofGetHeight(), 0, -(ofGetHeight() * 0.25));
    for (int i=0; i<videoControllers.size(); i++) {
        ofVec2f pos = ofVec2f(guiAnchor.x, guiAnchor.y + (i * (controllersSize.y + 60))); // EL +10 ES UN ESPACIO DE SEPARACION
        videoControllers[i].setPosition(pos.x,pos.y);
    }
}


void VideoManager::mousePressed(int x, int y, int button){
    
    // KEYFRAME SETTING + THUMBNAIL (IF RE-CLICKING ON ACTIVE VIDEO: JUMP TO SETED KEYFRAME)
    if (button == 0) {
        for (int i=0; i < videoControllers.size(); i++) {
            if(videoControllers[i].setKeyFrameSelection()){
                selectVideo(i);
                thumbSelection = videoControllers[i].getThumbForActiveKey();
                break;
            }
        }
    }
    
    // THUMBNAIL NAVIGATION AND VIDEO SELECTION (NO KEYFRAME SETTING OR JUMPING)
    if (button == 2) {
        for (int i=0; i < videoControllers.size(); i++) {
            int selectedKeyFrame = videoControllers[i].checkKeyFrameSelection();
            if(selectedKeyFrame >= 0){
                selectVideo(i);
                thumbSelection = videoControllers[i].getThumbForKey(selectedKeyFrame);
            }
        }
    }
    
}

void VideoManager::mouseDragged(int x, int y, int button){
    
    if (ofGetMouseX() > 1030 && ofGetMouseX() < 1045) {
        timelineScrollerY = ofGetMouseY();
        scrollTimeline();
    }
    
    
}
