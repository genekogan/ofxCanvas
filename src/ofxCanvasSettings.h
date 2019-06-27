#pragma once
#include "ofMain.h"

struct ofxCanvasSettings {
    string panelName;
    string name;
    ofColor color;
    bool isLine;
    float minWidth;
    float maxWidth;
    ofxCanvasSettings() {
        panelName = "";
        name = "";
        color = ofColor::black;
        isLine = true;
        minWidth = 0;
        maxWidth = 1;
    }
};
