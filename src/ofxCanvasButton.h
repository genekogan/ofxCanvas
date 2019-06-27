#pragma once

#include "ofMain.h"
#include "ofxCanvasSettings.h"
#include "ofxCanvasEvent.h"
#include "ofxClickable.h"



class ofxCanvasGuiElement : public ofxClickable {
public:
    ofxCanvasGuiElement();
    void setup(string msg, ofxCanvasSettings settings, int x, int y, int w, int h, bool isVertical);
    string getPanelName() {return settings.panelName;}
    ofxCanvasSettings settings;
    bool isVertical;
};


class ofxCanvasButton : public ofxCanvasGuiElement {
public:
    ofxCanvasButton() : ofxCanvasGuiElement() { }
    void buttonClicked();
};


class ofxCanvasSlider : public ofxCanvasGuiElement {
public:
    ofxCanvasSlider() : ofxCanvasGuiElement() { }
    void mouseDragged(int x, int y);
    void draw();
    void sliderChanged();
    float value;
};
