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
    void jumpBack();
    void toggleLoopSection();
    
    void switchToNextVideo();
    void switchToPreviousVideo();
    void switchToVideo(int videoID);
    
    //ofVec2f ofGetDisplayScale();

    
    ofFbo renderSurface;
    static ofVec2f renderSurfacePos;
    //static ofVec2f displayScale;
    
    int activeVideo;
    int selectedVideo;
    void selectVideo(int videoNum);
    void trigger();
    
    ofXml settings;
    
    // GUI VARS
    ofVec2f guiAnchor;
    ofVec2f controllersSize;
    
    void mousePressed();
    void keyPressed();
    
    
private:
    
    vector<VideoController> videoControllers;
    void buildVideoControllers(ofXml *settings);
    //void switchToVideo(int videoNum);
    
};