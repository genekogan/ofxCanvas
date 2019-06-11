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
    
    void addDrawOption(string name, ofColor color, bool isLine, float minWidth, float maxWidth, string iconPath);
    void addDrawOption(string name, ofColor color, bool isLine, float minWidth, float maxWidth) {addDrawOption(name, color, isLine, minWidth, maxWidth, "__NONE__");}
    
    void addLineOption(string name, ofColor color, float minWidth, float maxWidth, string iconPath);
    void addLineOption(string name, ofColor color, float minWidth, float maxWidth) {addLineOption(name, color, minWidth, maxWidth, "__NONE__");}
    
    void addShapeOption(string name, ofColor color, float minWidth, float maxWidth, string iconPath);
    void addShapeOption(string name, ofColor color, float minWidth, float maxWidth) {addShapeOption(name, color, minWidth, maxWidth, "__NONE__");}
    
    void addUndoOption(string name, string iconPath);
    void addUndoOption(string name) {addRedoOption(name, NULL);}
    void addRedoOption(string name, string iconPath);
    void addRedoOption(string name) {addRedoOption(name, NULL);}
    
    void addClearOption(string name, string iconPath);
    void addClearOption(string name) {addClearOption(name, NULL);}
    
    void addSlider(string name, float minValue, float maxValue);
    
    void clearButtons();
    
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y);
    void mousePressed(int x, int y);
    void mouseReleased(int x, int y);

    ofxCanvasGuiElement * getElement(int idx) {return buttons[idx];} 
    
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
