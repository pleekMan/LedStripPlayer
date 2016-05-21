#include "LedStripController.h"
#include "ofxXmlSettings.h"

#define RECONNECT_TIME 400

//--------------------------------------------------------------
void LedStripController::setup(){


    //create the socket and set to send to 127.0.0.1:11999
	udpConnection1.Create();
	udpConnection1.Connect("192.168.1.101",8888);
	udpConnection1.SetNonBlocking(true);
    
#ifdef USE_2_ARDUINOS
    udpConnection2.Create();
    udpConnection2.Connect("192.168.1.102",8888);
    udpConnection2.SetNonBlocking(true);
#endif
    
    
    ofxXmlSettings XML;
    if( XML.loadFile("LedStripsChannelAssignment.xml") ){
        ofLogVerbose("LedStripController") << "LedStripsChannelAssignment.xml loaded!";
    }else{
        ofLogError("LedStripController") << "unable to load LedStripsChannelAssignment.xml check data/ folder";
    }
    
    XML.pushTag("ARDUINO_1");

    int totalLeds = XML.getNumTags("LED");
    unsigned char *pBuffer = arduino1Buffer;
    
    for(int i=0; i<totalLeds; i++){
        XML.pushTag("LED", i);
        
        int channel = XML.getValue("CHANNEL", -1);
        int size = XML.getValue("SIZE", -1);
        
        if(channel>=0 && size >=0){
            channelMap[channel].size = size;
            channelMap[channel].p2Buffer = pBuffer;
            pBuffer += size*3;
        }
        else{
            ofLogError("LedStripController") << "LED INFO DISMISSED IN XML SETTINGS";
        }
        XML.popTag();
    }
    
    XML.popTag();
    
    cout << "channelMap:" << endl;
    for(int i=3; i<=8; i++){
        cout << i << ": ";
        cout << channelMap[i].size << "\t";
        cout << &channelMap[i].p2Buffer << endl;
    }
    
#ifdef USE_2_ARDUINOS
    if(XML.tagExists("ARDUINO_2")){
        XML.pushTag("ARDUINO_2");
        
        int totalLeds = XML.getNumTags("LED");
        pBuffer = arduino2Buffer;
        
        for(int i=0; i<totalLeds; i++){
            XML.pushTag("LED", i);
            
            int channel = XML.getValue("CHANNEL", -1);
            int size = XML.getValue("SIZE", -1);
            
            if(channel>=0 && size >=0){
                channelMap[channel].size = size;
                channelMap[channel].p2Buffer = pBuffer;
                pBuffer += size*3;
            }
            else{
                ofLogError("LedStripController") << "LED INFO DISMISSED IN XML SETTINGS";
            }
            XML.popTag();
        }
        
        XML.popTag();
    }
#endif
    /*
    unsigned char *pBuffer = arduino1Buffer;
    
    channelMap[1] = pBuffer;
    pBuffer += 60*3;
    channelMap[2] = pBuffer;
    pBuffer += 60*3;
    channelMap[3] = pBuffer;
    pBuffer += 60*3;
    channelMap[4] = pBuffer;
    pBuffer += 60*3;
    channelMap[5] = pBuffer;
    pBuffer += 30*3;
    channelMap[6] = pBuffer;
    
    pBuffer = arduino2Buffer;
    channelMap[7] = pBuffer;
    pBuffer += 60*3;
    channelMap[8] = pBuffer;
    pBuffer += 60*3;
    channelMap[9] = pBuffer;
    pBuffer += 60*3;
    channelMap[10] = pBuffer;
    pBuffer += 60*3;
    channelMap[11] = pBuffer;
    pBuffer += 30*3;
    channelMap[12] = pBuffer;
     */
}

//--------------------------------------------------------------
void LedStripController::update(){
    udpConnection1.Send((char *)arduino1Buffer,900);
#ifdef USE_2_ARDUINOS
    udpConnection2.Send((char *)arduino2Buffer,900);
#endif
}

//--------------------------------------------------------------
void LedStripController::setLedStrip(int channel, vector<ofColor>& colors){
    if(channel>=3 && channel <=8){
        unsigned char *pBuffer = channelMap[channel].p2Buffer;
        
        for(int i=0; i<channelMap[channel].size; i++){
            pBuffer[i*3+0] = colors[i].r;
            pBuffer[i*3+1] = colors[i].g;
            pBuffer[i*3+2] = colors[i].b;
        }
    }
    
}