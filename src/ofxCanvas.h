#pragma once

#include "ofMain.h"
#include "ofxCanvasSettings.h"
#include "ofxCanvasButton.h"
#include "ofxCanvasEvent.h"

// todo
// - when mouse released, "save last" for undo
// - smoother lines
// - better interface
// - perlin distortion



class ofxCanvas {
public:
    ofxCanvas();
    ~ofxCanvas();
    
    void setup(int x, int y, int width, int height, int guiWidth, bool guiIsVertical);
    void clearButtons();

    void addDrawOption(string msg, ofColor color, bool isLine, float minWidth, float maxWidth);
    void addShapeOption(string msg, ofColor color, float minWidth, float maxWidth);
    void addLineOption(string msg, ofColor color, float minWidth, float maxWidth);
    void addUndoOption(string msg);
    void addSlider(string msg, float minValue, float maxValue);

    void setBackground(ofColor clr);
    void setCurrentColor(ofColor clr);

    void undo();

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
    
    void savePrevious();

    void setFromPixels(ofPixels & pixels);
    void clear();

protected:
    
    void buttonEvent(ofxCanvasButtonEvent &e);
    void sliderEvent(ofxCanvasSliderEvent &e);
    
    vector<ofxCanvasGuiElement*> buttons;
    bool guiIsVertical;
    int guiWidth;
    int guiEnd;
    int width;
    int height;
    
    vector<ofVec2f> points;
    
    ofColor bgColor;
    ofColor currentColor;
    bool isLine;
    float minWidth, maxWidth;
    float value;
    
    ofRectangle canvasR;
    ofRectangle guiR;
    
    ofFbo canvas;
    bool changed;
    bool toClassify;
    
    vector<ofImage> previous;
};

