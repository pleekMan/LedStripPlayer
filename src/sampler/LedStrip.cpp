//
//  LedStrip.cpp
//  LedStripPlayer
//
//  Created by PleekMan on 14/5/2016.
//
//

#include "LedStrip.h"

void LedStrip::initialize(ofPoint _startPoint, ofPoint _endPoint, int _ledCount, int _ID){
    start = _startPoint;
    end = _endPoint;
    
    ledCount = _ledCount;
    ID = _ID;
    
}

void LedStrip::update(){
    
}

ofPoint LedStrip::getLedPosition(int led){
    
    float ledX = ofLerp(start.x, end.x, led / (float)ledCount);
    float ledY = ofLerp(start.y, end.y, led / (float)ledCount);
    return ofPoint(ledX,ledY);
    
}

int LedStrip::getLedCount(){
    return ledCount;
}

int LedStrip::getId(){
    return ID;
}