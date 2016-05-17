//
//  VideoManager.h
//  LedStripPlayer
//
//  Created by PleekMan on 14/5/2016.
//
//

#ifndef __LedStripPlayer__VideoManager__
#define __LedStripPlayer__VideoManager__

#include <iostream>
#include "ofMain.h"
#include "VideoController.h"

#endif /* defined(__LedStripPlayer__VideoManager__) */

class VideoManager{
    
    
public:
    VideoManager(){};
    
    void initialize(ofXml *_settings);
    void update();
    void render();
    ofFbo getRenderSurface();
    
    void jumpToNextKeyFrame();
    void jumpToPreviousKeyFrame();
    void toggleLoopSection();
    
    void jumpToNextVideo();
    void jumpToPreviousVideo();
    void jumpToVideo(int videoID);
    
    //ofVec2f ofGetDisplayScale();

    
    ofFbo renderSurface;
    //static ofVec2f displayScale;
    
    int activeVideo;
    
    ofXml settings;
    
    // GUI VARS
    ofVec2f guiAnchor;
    ofVec2f controllersSize;
    
    
private:
    
    vector<VideoController> videoControllers;
    void buildVideoControllers(ofXml *settings);
    void switchToVideo(int videoNum);
    
};