//
//  VideoManager.cpp
//  LedStripPlayer
//
//  Created by PleekMan on 14/5/2016.
//
//

#include "VideoManager.h"


void VideoManager::initialize(ofXml *_settings){
    
    guiAnchor = ofVec2f(10,10);
    controllersSize = ofVec2f(200,100);
    
    activeVideo = 0;

    renderSurface.allocate(200, 100, GL_RGB);
    renderSurface.begin();
    ofClear(0);
    renderSurface.end();
    
    //displayScale = ofVec2f(1.0);
    
    buildVideoControllers(_settings);
    videoControllers[0].setActive(true);
    
    
    
}

void VideoManager::buildVideoControllers(ofXml *settings){
    
    settings->setTo("//videos"); // AT VIDEOS
    
    // GET VIDEO DATA - BEGIN ------------------
    int videoCount = settings->getNumChildren();
    cout << "VideoCount: " << ofToString(videoCount) << endl;
    settings->setToChild(0); // AT FIRST VIDEO
    
    for (int i=0; i<videoCount; i++) {
        VideoController newVideoController;
        
        string videoPath = settings->getAttribute("path");
        cout << ofToString(i) << " - " << videoPath << endl;
        
        int keyCount = settings->getNumChildren();
        int keys[keyCount];
        
        settings->setToChild(0); // AT FIRST KEYFRAME
        for (int j=0; j<keyCount; j++) {
            keys[j] = settings->getValue<int>(""); // GET VALUE AT CURRENT NODE
            cout << ofToString(keys[j]) << endl;
            
            settings->setToSibling();
        }
        
        newVideoController.initialize(videoPath, keys, keyCount, &renderSurface);
        newVideoController.setSize(controllersSize.x, controllersSize.y);
        ofVec2f pos = ofVec2f(guiAnchor.x + 10, guiAnchor.y + (i * (controllersSize.y + 10))); // EL +10 ES UN ESPACIO DE SEPARACION
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
    
    //
    renderSurface.draw(700,10);
    
    // RENDER GUI FOR EACH VIDEO
    ofSetColor(255);
    for (int i=0; i<videoControllers.size(); i++) {
        videoControllers[i].render();
    }
    
    // SOME GUI SHIT
    ofNoFill();
    ofSetColor(0, 127, 127);
    ofRect(guiAnchor, 500,500);
    
}

void VideoManager::jumpToNextKeyFrame(){
    videoControllers[activeVideo].jumpToNextKeyFrame();
}

void VideoManager::jumpToPreviousKeyFrame(){
    videoControllers[activeVideo].jumpToPreviousKeyFrame();
}

void VideoManager::toggleLoopSection(){
    videoControllers[activeVideo].toggleLoopSection();
}

ofFbo VideoManager::getRenderSurface(){
    return renderSurface;
}
