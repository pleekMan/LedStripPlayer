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
        ofPoint end = ofPoint(ofToFloat(settings->getAttribute("xEnd")), ofToFloat(settings->getAttribute("yEnd")));
        int ledCount = ofToInt(settings->getAttribute("ledCount"));
        int ID = ofToInt(settings->getAttribute("id"));

        newLedStrip.initialize(start, end, ledCount,ID);
        ledStrips.push_back(newLedStrip);
        
        cout << "LedStrip: " << ofToString(ID) << " with " << ofToString(ledCount) << " leds" << endl;
        settings->setToSibling();
        
    }
}

void PixelSampler::setSamplingSurface(ofFbo *_samplingSurface){
    samplingSurface = _samplingSurface;
}

void PixelSampler::update(){
    
    
    
}

void PixelSampler::render(){
    
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
    
}
/*
unsigned char *PixelSampler::sampleLedStrip(int ledStrip){
    
    unsigned char charPixels[] = new char[ledStrips[ledStrip].getLedCount() * 3];
    unsigned char* pixels;
    
    //samplingSurface->readToPixels(pixels);

    ofPixels pix;
    samplingSurface->readToPixels(pix);
    
    //int counter = 0;
    for (int i=0; i < ledStrips[ledStrip].getLedCount(); i++) {
        
        float x = ledStrips[ledStrip].getLedPosition(i).x * samplingSurface->getWidth();
        float y = ledStrips[ledStrip].getLedPosition(i).y * samplingSurface->getHeight();
            
        ofColor color = pix.getColor(x, y);
        
        charPixels[i * 3 + 0] = color.r;
        charPixels[i * 3 + 1] = color.g;
        charPixels[i * 3 + 2] = color.b;
    }
    return charPixels;
}
 */

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