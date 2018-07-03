#include "ofxCanvas.h"



ofxCanvas::ofxCanvas() {
    currentColor = ofColor::black;
    isLine = true;
    lineWidth = 2;
    guiIsVertical = false;
}

ofxCanvas::~ofxCanvas() {
    clearButtons();
}

void ofxCanvas::clearButtons() {
    for (vector<ofxCanvasButton*>::iterator it = buttons.begin();
         it != buttons.end(); ++it) {
        delete (*it);
    }
    buttons.clear();
}

void ofxCanvas::setup(int x, int y, int width, int height, int guiWidth, bool guiIsVertical) {
    this->guiIsVertical = guiIsVertical;
    if (guiIsVertical) {
        guiR.set(x, y, guiWidth, height);
        canvasR.set(x + guiWidth + 20, y, width, height);
    } else {
        canvasR.set(x, y, width, height);
        guiR.set(x, y, guiWidth, height);
    }
    
    ofFbo::Settings settings;
    settings.useStencil = true;
    settings.height = height;
    settings.width = width;
    settings.internalformat = GL_RGB; //GL_RGBA32F_ARB;
    settings.numSamples = 1;
    
    canvas.allocate(settings);
    //canvas.allocate(width, height);
    
    ofPushMatrix();
    ofPushStyle();
    
    canvas.begin();
    
    ofFill();
    ofSetColor(255);
    ofDrawRectangle(0, 0, width, height);
    
    canvas.end();
    
    ofPopMatrix();
    ofPopStyle();
    
    changed = false;
    toClassify = false;
    
    ofAddListener(ofxCanvasButtonEvent::events, this, &ofxCanvas::buttonEvent);
}

void ofxCanvas::addDrawOption(string msg, ofColor clr, bool isLine) {
    int buttonWidth = 200;
    int buttonHeight = 75;
    int buttonMargin = 25;
    
    int n = buttons.size();
    int x = guiR.getX() + 5 + (buttonWidth + buttonMargin) * n;
    int y = guiR.getY() + buttonHeight - 5;
    
    ofxCanvasButton *b1 = new ofxCanvasButton();
    b1->setup(msg, clr, isLine, x, y, buttonWidth, buttonHeight);
    buttons.push_back(b1);
}

void ofxCanvas::setCanvasPosition(int x, int y) {
    canvasR.set(x, y, canvasR.getWidth(), canvasR.getHeight());
}

void ofxCanvas::setGuiPosition(int x, int y) {
    int x0 = guiR.getX();
    int y0 = guiR.getY();
    guiR.set(x, y, canvasR.getWidth(), canvasR.getHeight());
    // update buttons
    for (auto b: buttons) {
        // todo
    }
}

void ofxCanvas::update() {
    canvas.begin();
    
    ofSetColor(0);
    ofSetLineWidth(4);
    ofBeginShape();
    ofNoFill();
    for (int p=0; p<points.size(); p+=5) {
        ofCurveVertex(points[p].x, points[p].y);
    }
    ofEndShape();
    
    canvas.end();
}

//--------------------------------------------------------------
void ofxCanvas::buttonEvent(ofxCanvasButtonEvent &e) {
    currentColor = e.color;
    isLine = e.isLine;
    lineWidth = 2;//e.lineWidth;

}


//--------------------------------------------------------------
void ofxCanvas::drawGui(){
    ofPushStyle();
    ofSetColor(ofColor::black);
    ofDrawRectangle(guiR);
    for (int i=0; i<buttons.size(); i++) {
        buttons[i]->draw();
    }
    ofPopStyle();
}

//--------------------------------------------------------------
void ofxCanvas::draw(){
    ofPushMatrix();
    ofPushStyle();
    
    ofSetColor(255);
    canvas.draw(canvasR.getX(), canvasR.getY());
    
    //
    //    ofPushMatrix();
    //    ofTranslate(100, 100);
    //    ofSetColor(0);
    //    ofSetLineWidth(8);
    //    ofBeginShape();
    //    ofNoFill();
    ////    for (int p=0; p<points.size(); p+=10) {
    ////        ofCurveVertex(points[p].x, points[p].y);
    ////    }
    //    ofEndShape();
    //    ofPopMatrix();
    
    ofPopMatrix();
    ofPopStyle();
    
}

//--------------------------------------------------------------
bool ofxCanvas::isFrameNew() {
    if (changed) {
        changed = false;
        return true;
    } else {
        return false;
    }
}

//--------------------------------------------------------------
bool ofxCanvas::isShapeNew() {
    if (toClassify) {
        toClassify = false;
        return true;
    } else {
        return false;
    }
}

//--------------------------------------------------------------
void ofxCanvas::mouseMoved(int x, int y){
    for (auto b : buttons) {
        b->mouseMoved(x, y);
    }
}

//--------------------------------------------------------------
void ofxCanvas::mouseDragged(int x, int y){
    for (auto b : buttons) {
        b->mouseDragged(x, y);
    }

    float x1 = ofGetPreviousMouseX()-canvasR.getX();
    float y1 = ofGetPreviousMouseY()-canvasR.getY();
    float x2 = ofGetMouseX()-canvasR.getX();
    float y2 = ofGetMouseY()-canvasR.getY();
    
    // when should this change
    changed = true;
    
    
    canvas.begin();
    
    ofSetColor(currentColor);
    //ofSetLineWidth(8);
    ofSetLineWidth(lineWidth);
    ofBeginShape();
    ofNoFill();
    ofDrawLine(x1, y1, x2, y2);
    ofEndShape();
    
    canvas.end();
    
    //points.push_back(ofVec2f(x2, y2));
}

//--------------------------------------------------------------
void ofxCanvas::mousePressed(int x, int y){
    for (auto b : buttons) {
        b->mousePressed(x, y);
    }

}

//--------------------------------------------------------------
void ofxCanvas::mouseReleased(int x, int y){
    for (auto b : buttons) {
        b->mouseReleased(x, y);
    }

    update();
    toClassify = true;
    points.clear();
}
