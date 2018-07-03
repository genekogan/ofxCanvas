#pragma once

#include "ofMain.h"
#include "ofxCanvasButtonEvent.h"


class ofxCanvasGuiElement {
public:
    ofxCanvasGuiElement();
    void setup(string msg, ofColor color, bool isLine, int x, int y, int w, int h, bool isVertical);
    
    virtual void draw() { }

    virtual void mouseMoved(int x, int y);
    virtual void mouseDragged(int x, int y);
    virtual void mousePressed(int x, int y);
    virtual void mouseReleased(int x, int y);
    
    ofRectangle button;
    string msg;
    ofColor color;
    bool isLine;
    bool isHover, isPressed;
    bool isVertical;
};


class ofxCanvasButton : public ofxCanvasGuiElement {
public:
    ofxCanvasButton() : ofxCanvasGuiElement() { }
    void mouseReleased(int x, int y);
    void buttonClicked();
    void draw();
};


class ofxCanvasSlider : public ofxCanvasGuiElement {
public:
    ofxCanvasSlider() : ofxCanvasGuiElement() { }
    void mouseDragged(int x, int y);
    void draw();
    
    float value;
};
