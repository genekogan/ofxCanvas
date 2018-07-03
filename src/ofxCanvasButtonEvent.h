#pragma once
#include "ofMain.h"


class ofxCanvasButtonEvent : public ofEventArgs {
public:
    ofColor color;
    bool isLine;
    
    ofxCanvasButtonEvent() {
        color = ofColor(0);
        isLine = false;
    }
    
    static ofEvent<ofxCanvasButtonEvent> events;
};
