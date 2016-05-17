//
//  LedStrip.h
//  LedStripPlayer
//
//  Created by PleekMan on 14/5/2016.
//
//

#ifndef __LedStripPlayer__LedStrip__
#define __LedStripPlayer__LedStrip__

#include <iostream>
#include "ofMain.h"

#endif /* defined(__LedStripPlayer__LedStrip__) */

class LedStrip{
    
public:
    void initialize(ofPoint _startPoint, ofPoint _endPoint, int _ledCount, int _ID);
    void update();
    
    ofPoint start, end;
    int ledCount;
    int ID;
    
    ofPoint getLedPosition(int led);
    int getLedCount();
    
    
    
private:
    
};