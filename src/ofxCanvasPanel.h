#pragma once

#include "ofMain.h"
#include "ofxCanvasSettings.h"
#include "ofxCanvasButton.h"
#include "ofxCanvasEvent.h"
#include "ofxCanvas.h"


class ofxCanvas;

class ofxCanvasPanel  {
public:
    ofxCanvasPanel();
    ~ofxCanvasPanel();
    
    void setup(int x, int y, int guiWidth, bool guiIsVertical, ofxCanvas *canvas);
    void setPosition(int x, int y);
    
    void draw();
    
    void addDrawOption(string msg, ofColor color, bool isLine, float minWidth, float maxWidth, string iconPath);
    void addDrawOption(string msg, ofColor color, bool isLine, float minWidth, float maxWidth) {addDrawOption(msg, color, isLine, minWidth, maxWidth, "__NONE__");}
    
    void addLineOption(string msg, ofColor color, float minWidth, float maxWidth, string iconPath);
    void addLineOption(string msg, ofColor color, float minWidth, float maxWidth) {addLineOption(msg, color, minWidth, maxWidth, "__NONE__");}
    
    void addShapeOption(string msg, ofColor color, float minWidth, float maxWidth, string iconPath);
    void addShapeOption(string msg, ofColor color, float minWidth, float maxWidth) {addShapeOption(msg, color, minWidth, maxWidth, "__NONE__");}
    
    void addUndoOption(string msg, string iconPath);
    void addUndoOption(string msg) {addUndoOption(msg, NULL);}
    
    void addClearOption(string msg, string iconPath);
    void addClearOption(string msg) {addClearOption(msg, NULL);}
    
    void addSlider(string msg, float minValue, float maxValue);
    
    void clearButtons();
    
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y);
    void mousePressed(int x, int y);
    void mouseReleased(int x, int y);
    
protected:
    
    void buttonEvent(ofxCanvasButtonEvent &e);
    void sliderEvent(ofxCanvasSliderEvent &e);
    
    ofxCanvas *canvas;
    
    vector<ofxCanvasGuiElement*> buttons;
    bool guiIsVertical;
    int guiWidth;
    int guiEnd;
    
    ofRectangle guiR;
    
};
