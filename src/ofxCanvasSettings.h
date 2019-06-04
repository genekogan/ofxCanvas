#pragma once
#include "ofMain.h"

struct ofxCanvasSettings {
    string name;
    ofColor color;
    bool isLine;
    float minWidth;
    float maxWidth;
    ofxCanvasSettings() {
        name = "";
        color = ofColor::black;
        isLine = true;
        minWidth = 0;
        maxWidth = 1;
    }
};
