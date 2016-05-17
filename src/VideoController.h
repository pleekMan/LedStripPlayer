//
//  VideoController.h
//  LedStripPlayer
//
//  Created by PleekMan on 14/5/2016.
//
//

#ifndef __LedStripPlayer__VideoController__
#define __LedStripPlayer__VideoController__

#include <iostream>
#include "ofMain.h"

#endif /* defined(__LedStripPlayer__VideoController__) */

typedef struct{
    string name;
    unsigned int frame;
}KeyFrame;

class VideoController{
    
public:
    VideoController(){};
    
    void initialize(string videoPath, int _keyFrames[], int totalKeys, ofFbo *_renderSurface);
    void update();
    void render();
    
    int getCurrentFrame();
    int getTotalFrames();
    
    void jumpToNextKeyFrame();
    void jumpToPreviousKeyFrame();
    void jumpBack();
    void updateKeyFrames(int keyFrame);
    void toggleLoopSection();
    void setActive(bool state);

    
    ofVideoPlayer videoMain;
    vector<KeyFrame> keyFrames;
    int totalFrames;
    int atKeyFrame;
    int inFrame, outFrame;
    bool isActive;
    
    bool sectionLoop;

    ofFbo *renderSurface;
    
    // GUI vars
    ofVec2f position;
    ofVec2f size;
    
    void setPosition(float _x, float _y);
    void setSize(float width, float height);
    
    
    
private:
    
    void setInOutFrames(int _inFrame, int _outFrame);
    
};