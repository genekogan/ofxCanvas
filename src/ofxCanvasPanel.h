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
    
    string getPanelName() {return panelName;}
    
    void setup(string panelName, int x, int y, int guiWidth, bool guiIsVertical, ofxCanvas *canvas);
    void setPosition(int x, int y);
    
    void draw();
    
    ofxCanvasGuiElement * addDrawOption(string name, ofColor color, bool isLine, float minWidth, float maxWidth, string iconPath);
    ofxCanvasGuiElement * addDrawOption(string name, ofColor color, bool isLine, float minWidth, float maxWidth) {return addDrawOption(name, color, isLine, minWidth, maxWidth, "__NONE__");}
    
    ofxCanvasGuiElement * addLineOption(string name, ofColor color, float minWidth, float maxWidth, string iconPath);
    ofxCanvasGuiElement * addLineOption(string name, ofColor color, float minWidth, float maxWidth) {return addLineOption(name, color, minWidth, maxWidth, "__NONE__");}
    
    ofxCanvasGuiElement * addShapeOption(string name, ofColor color, float minWidth, float maxWidth, string iconPath);
    ofxCanvasGuiElement * addShapeOption(string name, ofColor color, float minWidth, float maxWidth) {return addShapeOption(name, color, minWidth, maxWidth, "__NONE__");}
    
    ofxCanvasGuiElement * addUndoOption(string name, string iconPath);
    ofxCanvasGuiElement * addUndoOption(string name) {return addRedoOption(name, NULL);}
    ofxCanvasGuiElement * addRedoOption(string name, string iconPath);
    ofxCanvasGuiElement * addRedoOption(string name) {return addRedoOption(name, NULL);}
    
    ofxCanvasGuiElement * addClearOption(string name, string iconPath);
    ofxCanvasGuiElement * addClearOption(string name) {return addClearOption(name, NULL);}

    ofxCanvasGuiElement * addBrushSizeOption(string name, int value, string iconPath);
    ofxCanvasGuiElement * addBrushSizeOption(string name, int value) {return addBrushSizeOption(name, value, NULL);}

    ofxCanvasGuiElement * addMiscOption(string name, string iconPath);
    ofxCanvasGuiElement * addMiscOption(string name) {return addMiscOption(name, NULL);}

    ofxCanvasGuiElement * addSlider(string name, float minValue, float maxValue);
    
    void clearButtons();
    
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y);
    void mousePressed(int x, int y);
    void mouseReleased(int x, int y);

    ofxCanvasGuiElement * getElement(int idx) {return buttons[idx];}
    vector<ofxCanvasGuiElement*> getElements() {return buttons;}
    
protected:
    
    void buttonEvent(ofxCanvasButtonEvent &e);
    void sliderEvent(ofxCanvasSliderEvent &e);
    
    ofxCanvas *canvas;
    
    vector<ofxCanvasGuiElement*> buttons;
    bool guiIsVertical;
    int guiWidth;
    int guiEnd;
    string panelName;    
    ofRectangle guiR;
    
};
