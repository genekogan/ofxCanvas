#pragma once

#include "ofMain.h"
#include "ofxCanvasSettings.h"
#include "ofxCanvasEvent.h"


class ofxCanvasGuiElement {
public:
    ofxCanvasGuiElement();
    void setup(string msg, ofxCanvasSettings settings, int x, int y, int w, int h, bool isVertical);
    
    virtual void addIcon(string iconPath);
    virtual void draw() { }

    virtual void mouseMoved(int x, int y);
    virtual void mouseDragged(int x, int y);
    virtual void mousePressed(int x, int y);
    virtual void mouseReleased(int x, int y);
    
    ofxCanvasSettings settings;

    ofImage icon;
    ofRectangle button;
    string msg;
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
    void sliderChanged();
    
    float value;
};
