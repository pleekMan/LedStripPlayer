#pragma once

#include "ofxNetwork.h"
#include "ofMain.h"

//#define USE_2_ARDUINOS

class LedStripController{

	public:
		void setup();
		void update();
		void setLedStrip(int channel, vector<ofColor>& colors);
		

		ofxUDPManager udpConnection1;
#ifdef USE_2_ARDUINOS
    	ofxUDPManager udpConnection2;
#endif
    
    
        //Buffer for saving current led strips colors.
        //Each led is represented by 3 bytes (R,G,B)
        //Because each Arduino controls 4 long strips (60 leds each) and 2 short strips (30 leds each), the total buffer size is (60*4+30*2)*3=900 bytes
        unsigned char arduino1Buffer[900];
        unsigned char arduino2Buffer[900];
    
        //Channel assignment
        typedef struct{
            unsigned char* p2Buffer;
            unsigned int size;
        }LedStripData;
    
        map<int, LedStripData> channelMap;
};

