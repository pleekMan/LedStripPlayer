//
//  PixelSampler.h
//  LedStripPlayer
//
//  Created by PleekMan on 14/5/2016.
//
//

#ifndef __LedStripPlayer__PixelSampler__
#define __LedStripPlayer__PixelSampler__

#include <iostream>
#include "ofMain.h"
#include "LedStrip.h"
#include "VideoManager.h"

#endif /* defined(__LedStripPlayer__PixelSampler__) */

class PixelSampler{
    
public:
    
    void initialize(ofXml *_settings);
    void setSamplingSurface(ofFbo *_samplingSurface);
    void update();
    void render();
    //unsigned char *sampleLedStrip(int ledStrip);
    
    int ledStripCount;
    vector<LedStrip> ledStrips;
    int totalLedCount;
    
    ofFbo *samplingSurface;
    
    
    
private:
    void buildLedStrips(ofXml *settings);
    
};