#include "ofxCanvasButton.h"

//--------------------------------------------------------------
ofxCanvasGuiElement::ofxCanvasGuiElement() {
    isHover = false;
    isPressed = false;
    isVertical = false;
}

//--------------------------------------------------------------
void ofxCanvasGuiElement::setup(string msg, ofxCanvasSettings settings, int x, int y, int w, int h, bool isVertical) {
    this->msg = msg;
    this->settings = settings;
    this->isVertical = isVertical;
    button = ofRectangle(x, y, w, h);
}

//--------------------------------------------------------------
void ofxCanvasGuiElement::mouseMoved(int x, int y){
    isHover = button.inside(x, y);
}

//--------------------------------------------------------------
void ofxCanvasGuiElement::mouseDragged(int x, int y){
    
}

//--------------------------------------------------------------
void ofxCanvasGuiElement::mousePressed(int x, int y){
    if (isHover) {
        isPressed = true;
    }
}

//--------------------------------------------------------------
void ofxCanvasGuiElement::mouseReleased(int x, int y){
    if (isPressed) {
        isPressed = false;
    }
}

//--------------------------------------------------------------
void ofxCanvasButton::mouseReleased(int x, int y){
    if (isPressed) {
        isPressed = false;
        buttonClicked();
    }
}

//--------------------------------------------------------------
void ofxCanvasButton::draw(){
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
void ofxCanvasSlider::mouseDragged(int x, int y){
    if (isHover) {
        if (isVertical) {
            value = (y - button.getY()) / button.getHeight();
            value = ofClamp(value, 0, 1);
        } else {
            value = (x - button.getX()) / button.getWidth();
            value = ofClamp(value, 0, 1);
        }
        sliderChanged();
    }
}

//--------------------------------------------------------------
void ofxCanvasSlider::draw(){
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
    
    ofSetColor(0, 255, 0);
    if (isVertical) {
        ofDrawRectangle(button.getX(), button.getY() + value * button.getHeight(), button.getWidth(), 5);
    } else {
        ofDrawRectangle(button.getX() + value * button.getWidth(), button.getY(), 5, button.getHeight());
    }
    
    ofDrawBitmapString(msg, button.x, button.y+20);
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

