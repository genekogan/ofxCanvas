#pragma once

#include "ofMain.h"
#include "ofxCanvasButton.h"
#include "ofxCanvasButtonEvent.h"

// todo
// - when mouse released, "save last" for undo
// - smoother lines
// - better interface

class ofxCanvas {
public:
    ofxCanvas();
    ~ofxCanvas();
    
    void setup(int x, int y, int width, int height, int guiWidth, bool guiIsVertical);
    void clearButtons();

    void addDrawOption(string msg, ofColor clr, bool isLine);
    void buttonEvent(ofxCanvasButtonEvent &e);

    void setCanvasPosition(int x, int y);
    void setGuiPosition(int x, int y);

    void update();
    void draw();
    void drawGui();
    
    ofFbo & getCanvas() {return canvas;}
    bool isFrameNew();
    bool isShapeNew();
    
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y);
    void mousePressed(int x, int y);
    void mouseReleased(int x, int y);
    
    
    
    vector<ofxCanvasButton*> buttons;
    bool guiIsVertical;
    
    vector<ofVec2f> points;
    
    ofColor currentColor;
    bool isLine;
    int lineWidth;
    
    ofRectangle canvasR;
    ofRectangle guiR;
    
    ofFbo canvas;
    bool changed;
    bool toClassify;
};

