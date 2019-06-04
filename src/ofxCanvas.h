#pragma once

#include "ofMain.h"
#include "ofxCanvasSettings.h"
#include "ofxCanvasButton.h"
#include "ofxCanvasEvent.h"

#include "ofxCanvasPanel.h"


class ofxCanvasPanel;

class ofxCanvas {
public:
    friend class ofxCanvasPanel;
    
    ofxCanvas();
    ~ofxCanvas();

    void addPanel(ofxCanvasPanel * panel);

    void setup(int x, int y, int width, int height);
    void setBackground(ofColor clr);
    void setCurrentColor(ofColor clr);

    void undo();

    void setPosition(int x, int y);
    
    void update();
    void draw();
    void drawPanels();
    
    ofFbo & getCanvas() {return canvas;}
    bool isFrameNew();
    bool isShapeNew();
    
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y);
    void mousePressed(int x, int y);
    void mouseReleased(int x, int y);
    
    void savePrevious();

    void setFromPixels(ofPixels & pixels);
    void setFromImage(string path);
    void clear();
    
    ofRectangle getRectangle() {return canvasR;}
    
protected:
    
    int width;
    int height;
    bool isLine;
    float minWidth, maxWidth;
    float value;
    ofColor bgColor;
    ofColor currentColor;

    ofRectangle canvasR;
    ofFbo canvas;
    bool changed;
    bool toClassify;
    bool toSavePrev;
    bool toUndo;
    bool toClear;
    
    vector<ofImage> previous;
    vector<ofVec2f> points;
    vector<ofxCanvasPanel*> panels;

};

