#pragma once
#include "ofMain.h"
#include "ofxCanvasSettings.h"

class ofxCanvasButtonEvent : public ofEventArgs {
public:
    ofxCanvasSettings settings;
    float value=0.0;
    ofxCanvasButtonEvent() {}
    static ofEvent<ofxCanvasButtonEvent> events;
};


class ofxCanvasSliderEvent : public ofEventArgs {
public:
    ofxCanvasSettings settings;
    float value=0.0;
    ofxCanvasSliderEvent() {}
    static ofEvent<ofxCanvasSliderEvent> events;
};

