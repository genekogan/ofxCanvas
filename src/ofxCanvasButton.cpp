#include "ofxCanvasButton.h"


//--------------------------------------------------------------
ofxCanvasGuiElement::ofxCanvasGuiElement() : ofxClickable() {
    isVertical = false;
}

//--------------------------------------------------------------
void ofxCanvasGuiElement::setup(string msg, ofxCanvasSettings settings, int x, int y, int w, int h, bool isVertical) {
    ofxClickable::setup(msg, x, y, w, h);
    this->isVertical = isVertical;
    this->settings = settings;
}

//--------------------------------------------------------------
void ofxCanvasSlider::mouseDragged(int x, int y){
    if (isHover) {
        if (isVertical) {
            value = (y - rect.getY()) / rect.getHeight();
            value = ofClamp(value, 0, 1);
        } else {
            value = (x - rect.getX()) / rect.getWidth();
            value = ofClamp(value, 0, 1);
        }
        sliderChanged();
    }
}

//--------------------------------------------------------------
void ofxCanvasSlider::draw(){
    ofPushStyle();

    if (isActive) {
        ofSetColor(cActive);
    }
    if (isHover) {
        ofSetColor(cHover);
    }
    if (isPressed) {
        ofSetColor(cPressed);
    }
    
    ofFill();
    ofDrawRectangle(rect);
    ofSetColor(0);
    
    ofSetColor(0, 255, 0);
    if (isVertical) {
        ofDrawRectangle(rect.getX(), rect.getY() + value * rect.getHeight(), rect.getWidth(), 5);
    } else {
        ofDrawRectangle(rect.getX() + value * rect.getWidth(), rect.getY(), 5, rect.getHeight());
    }
    
    ofDrawBitmapString(name, rect.getX(), rect.getY()+20);
    ofPopStyle();
}


//--------------------------------------------------------------
void ofxCanvasButton::buttonClicked() {
    static ofxCanvasButtonEvent newEvent;
    newEvent.settings = settings;
    ofNotifyEvent(ofxCanvasButtonEvent::events, newEvent);
}

//--------------------------------------------------------------
void ofxCanvasSlider::sliderChanged() {
    static ofxCanvasSliderEvent newEvent;
    newEvent.value = value;
    newEvent.settings = settings;
    ofNotifyEvent(ofxCanvasSliderEvent::events, newEvent);
}

