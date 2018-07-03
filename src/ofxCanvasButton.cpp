#include "ofxCanvasButton.h"

//--------------------------------------------------------------
ofxCanvasButton::ofxCanvasButton() {
    isHover = false;
    isPressed = false;
}

//--------------------------------------------------------------
void ofxCanvasButton::setup(string msg, ofColor color, bool isLine, int x, int y, int w, int h) {
    this->msg = msg;
    this->color = color;
    this->isLine = isLine;
    button = ofRectangle(x, y, w, h);
}

//--------------------------------------------------------------
void ofxCanvasButton::draw() {
    ofPushStyle();
    if (isPressed) {
        ofSetColor(ofColor::red);
    } else if (isHover) {
        ofSetColor(ofColor::orange);
    } else {
        ofSetColor(ofColor::white);
    }
    ofFill();
    ofDrawRectangle(button);
    ofSetColor(0);
    
    ofDrawBitmapString(msg, button.x, button.y+20);
    ofPopStyle();
}

//--------------------------------------------------------------
void ofxCanvasButton::buttonClicked() {
    static ofxCanvasButtonEvent newEvent;
    newEvent.color = color;
    newEvent.isLine = isLine;
    ofNotifyEvent(ofxCanvasButtonEvent::events, newEvent);
}

//--------------------------------------------------------------
void ofxCanvasButton::mouseMoved(int x, int y){
    isHover = button.inside(x, y);
}

//--------------------------------------------------------------
void ofxCanvasButton::mouseDragged(int x, int y){
    
}

//--------------------------------------------------------------
void ofxCanvasButton::mousePressed(int x, int y){
    if (isHover) {
        isPressed = true;
    }
}

//--------------------------------------------------------------
void ofxCanvasButton::mouseReleased(int x, int y){
    if (isPressed) {
        isPressed = false;
        buttonClicked();
    }
}



