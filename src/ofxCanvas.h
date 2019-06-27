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
    void setMaxHistory(int maxHistory) {this->maxHistory = maxHistory;}
    
    void undo();
    void redo();

    void setPosition(int x, int y);
    
    void update();
    void draw();
    void drawPanels();
    
    int getMaxHistory() {return maxHistory;}
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
    bool toClear;
    
protected:
    
    void resetMouse();
    
    int width;
    int height;
    bool isLine;
    float minWidth, maxWidth;
    float value;
    int maxHistory;
    ofColor bgColor;
    ofColor currentColor;

    ofRectangle canvasR;
    ofFbo canvas;
    ofImage canvasOut;
    bool changed;
    bool toClassify;
    bool toSavePrev;
    bool toUndo;
    bool toRedo;
    
    vector<ofImage> previous;
    vector<ofVec2f> points;
    vector<ofxCanvasPanel*> panels;

    ofVec2f mouse, prevMouse;
};

