//
//  PixelSampler.cpp
//  LedStripPlayer
//
//  Created by PleekMan on 14/5/2016.
//
//

#include "PixelSampler.h"


void PixelSampler::initialize( ofXml *_settings){
    
    buildLedStrips(_settings);
    
}

void PixelSampler::buildLedStrips(ofXml *settings){
    settings->setTo("//ledStrips");
    totalLedCount = settings->getNumChildren();

    settings->setToChild(0); // GOT TO FIRST LEDSTRIP
    
    
    for (int i=0; i < totalLedCount; i++) {
        LedStrip newLedStrip;
        ofPoint start = ofPoint(ofToFloat(settings->getAttribute("xStart")), ofToFloat(settings->getAttribute("yStart")));
        ofPoint end = ofPoint(ofToFloat(settings->getAttribute("xStop")), ofToFloat(settings->getAttribute("yStop")));
        int ledCount = ofToInt(settings->getAttribute("ledCount"));
        int ID = ofToInt(settings->getAttribute("id"));

        newLedStrip.initialize(start, end, ledCount,ID);
        ledStrips.push_back(newLedStrip);
        
        //cout << "LedStrip: " << ofToString(ID) << " with " << ofToString(ledCount) << " leds" << endl;
        cout << "LedStrip: " << ofToString(ID) << " :: Start: " << ofToString(start) << " --- End: " << ofToString(end) << endl;
        settings->setToSibling();
        
    }
}

void PixelSampler::setSamplingSurface(ofFbo *_samplingSurface){
    samplingSurface = _samplingSurface;
}

void PixelSampler::update(){
    
    
    
}

void PixelSampler::render(){
    
    previewLedStrips();
    
    
    /*
    ofFill();
    ofSetColor(0, 0, 255);
    for (int i=0; i<ledStrips.size(); i++) {
        for (int j=0; j<ledStrips[i].ledCount; j++) {
            float x = ledStrips[i].getLedPosition(j).x;
            float y = ledStrips[i].getLedPosition(j).y;
            
            //ofCircle(x * samplingSurface->getWidth() * VideoManager::displayScale.x, y * samplingSurface->getHeight() * VideoManager::displayScale.y, 1);
        }
    }
    
    //cout << ofToString(ledStrips.size()) << endl;
    //samplingSurface->get
    */
}

vector<ofColor> PixelSampler::sampleLedStrip(int ledStrip){
    
    //unsigned char charPixels[] = new char[ledStrips[ledStrip].getLedCount() * 3];
    //unsigned char* pixels;
    
    //samplingSurface->readToPixels(pixels);

    ofPixels pix;
    samplingSurface->readToPixels(pix);
    
    vector<ofColor> ledsColor;
    
    //int counter = 0;
    for (int i=0; i < ledStrips[ledStrip].getLedCount(); i++) {
        
        float x = ledStrips[ledStrip].getLedPosition(i).x * pix.getWidth();
        float y = ledStrips[ledStrip].getLedPosition(i).y * pix.getHeight();
            
        ofColor color = pix.getColor(x, y);
        ledsColor.push_back(color);
        

    }
    return ledsColor;
}

void PixelSampler::previewLedStrips(){
    //int i = 2;
    
    ofVec2f previewSize = ofVec2f(500,250);
    ofVec2f previewPos = ofVec2f(ofGetWindowWidth(),ofGetWindowHeight()) - previewSize;

    ofFill();
    ofSetColor(0);
    ofRect(previewPos.x, previewPos.y,  previewSize.x, previewSize.y);
    
    for (int i=0; i<ledStrips.size(); i++) {
        
        vector<ofColor> ledStripColor = sampleLedStrip(i);
        
        for (int j=0; j<ledStrips[i].getLedCount(); j++) {
            float x = previewPos.x + (ledStrips[i].start.x * previewSize.x);
            float y = previewPos.y +  (ofLerp(ledStrips[i].start.y, ledStrips[i].end.y, j / (float)ledStrips[i].getLedCount()) * previewSize.y);
            
            ofFill();
            ofSetColor(ledStripColor[j]);
            
            ofCircle(x,y, 3);
            
            //ofSetColor(255, 0, 0);
            //ofDrawBitmapString(ofToString(j), x + 5,y);
        }
        
    }
    
    // SHOW STRIPS OVERLAYING SAMPLING-SURFACE
    for (int i=0; i<ledStrips.size(); i++) {
        ofNoFill();
        ofSetColor(0, 255, 0);
        
        //ofVec2f start = ofVec2f(700 + (200 * ledStrips[i].start.x), 10 + (100 * ledStrips[i].start.y));
        ofVec2f start = ofVec2f(700 + (200 * ledStrips[i].end.x), 10 + (100 * ledStrips[i].start.y));
        ofVec2f end = ofVec2f(700 + (200 * ledStrips[i].end.x), 10 + (100 * ledStrips[i].end.y));
        
        ofLine(start.x, start.y, end.x, end.y);

        
        
    }
}

/*
unsigned char[] PixelSampler::sampleLedStrip(int ledStrip){
    
    char[] pixels; = new char[totalLedCount * 3];
    
    int counter = 0;
    for (int i=0; i<ledStrips.size(); i++) {
        for (int j=0; j<ledStrips[i].ledCount; j++) {
            float x = ledStrips[i].getLedPosition(j).x;
            float y = ledStrips[i].getLedPosition(j).y;
            
            pixels[counter + 0] = samplingSurface;
            
            counter+=3;
            
            
            //ofCircle(x * samplingSurface->getWidth() * VideoManager.displayScale.x, y * samplingSurface->getHeight() * VideoManager.displayScale.y, 1);
        }
    }
}
*/