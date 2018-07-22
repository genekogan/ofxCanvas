#pragma once
#include "ofMain.h"

struct ofxCanvasSettings {
    ofColor color;
    bool isLine;
    float minWidth;
    float maxWidth;
    ofxCanvasSettings() {
        color = ofColor::black;
        isLine = true;
        minWidth = 0;
        maxWidth = 1;
    }
};
