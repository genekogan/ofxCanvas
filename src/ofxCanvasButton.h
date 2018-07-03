#pragma once
#include "ofMain.h"


#include "ofxCanvasButtonEvent.h"


class ofxCanvasButton {
public:
    ofxCanvasButton();
    void setup(string msg, ofColor color, bool isLine, int x, int y, int w, int h);
    
    void buttonClicked();
    void draw();

    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y);
    void mousePressed(int x, int y);
    void mouseReleased(int x, int y);
    
    ofRectangle button;
    string msg;
    ofColor color;
    bool isLine;
    bool isHover, isPressed;
};
