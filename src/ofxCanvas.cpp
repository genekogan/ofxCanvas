#include "ofxCanvas.h"


//--------------------------------------------------------------
ofxCanvas::ofxCanvas() {
    currentColor = ofColor::black;
    isLine = true;
    value = 0.5;
    minWidth = 1;
    maxWidth = 5;
    bgColor = ofColor(255);
    toUndo = false;
    toClear = false;
}

//--------------------------------------------------------------
ofxCanvas::~ofxCanvas() {
}

//--------------------------------------------------------------
void ofxCanvas::setup(int x, int y, int width, int height) {
    this->width = width;
    this->height = height;
    canvasR.set(x, y, width, height);
    
    ofFbo::Settings settings;
    settings.useStencil = true;
    settings.height = height;
    settings.width = width;
    settings.internalformat = GL_RGB; //GL_RGBA32F_ARB;
    settings.numSamples = 1;
    
    canvas.allocate(settings);
    clear();

    changed = false;
    toClassify = false;
    toSavePrev = false;
    toUndo = false;
    toClear = false;

    savePrevious();
}

//--------------------------------------------------------------
void ofxCanvas::addPanel(ofxCanvasPanel * panel) {
    panels.push_back(panel);
}

//--------------------------------------------------------------
void ofxCanvas::clear() {
    ofPushMatrix();
    ofPushStyle();
    
    canvas.begin();
    
    ofFill();
    ofSetColor(bgColor);
    ofDrawRectangle(0, 0, width, height);
    
    canvas.end();
    
    ofPopMatrix();
    ofPopStyle();

    changed = true;
    toSavePrev = true;
    toClassify = true;
}


//--------------------------------------------------------------
void ofxCanvas::setFromPixels(ofPixels & pixels) {
    ofPushMatrix();
    ofPushStyle();
    
    ofImage newImg;
    newImg.setFromPixels(pixels);
    newImg.resize(width, height);

    canvas.begin();
    
    ofFill();
    ofSetColor(bgColor);
    ofDrawRectangle(0, 0, width, height);
    ofSetColor(255);
    newImg.draw(0, 0);
    
    canvas.end();
    
    ofPopMatrix();
    ofPopStyle();
    
    savePrevious();
}

//--------------------------------------------------------------
void ofxCanvas::setFromImage(string path) {
    ofImage img;
    img.load(path);
    setFromPixels(img.getPixels());
}

//--------------------------------------------------------------
void ofxCanvas::setBackground(ofColor clr) {
    bgColor = clr;
    clear();
}

//--------------------------------------------------------------
void ofxCanvas::setPosition(int x, int y) {
    canvasR.set(x, y, canvasR.getWidth(), canvasR.getHeight());
}

//--------------------------------------------------------------
void ofxCanvas::update() {
    if (toClear) {
        clear();
        toClear = false;
    }
    if (toUndo) {
        undo();
        toUndo = false;
    }

    canvas.begin();
    
    ofSetColor(0);
    ofSetLineWidth(value);
    ofBeginShape();
    ofNoFill();
    for (int p=0; p<points.size(); p+=5) {
        ofCurveVertex(points[p].x, points[p].y);
    }
    ofEndShape();
    
    canvas.end();
}

//--------------------------------------------------------------
void ofxCanvas::setCurrentColor(ofColor clr) {
    currentColor = clr;
}


//--------------------------------------------------------------
void ofxCanvas::undo() {
    if (previous.size() < 2) {
        return;
    }
    
    canvas.begin();
    previous[previous.size()-2].draw(0, 0);
    canvas.end();
    previous.pop_back();

    changed = true;
    toClassify = true;
}

//--------------------------------------------------------------
void ofxCanvas::savePrevious() {
    ofImage prev;
    canvas.readToPixels(prev);
    previous.push_back(prev);
}

//--------------------------------------------------------------
void ofxCanvas::drawPanels(){
    for (auto panel : panels) {
        panel->draw();
    }
}

//--------------------------------------------------------------
void ofxCanvas::draw(){
    ofPushMatrix();
    ofPushStyle();
    
    ofSetColor(255);
    canvas.draw(canvasR.getX(), canvasR.getY());
    
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
    for (auto panel : panels) {
        panel->mouseMoved(x, y);
    }
}

//--------------------------------------------------------------
void ofxCanvas::mouseDragged(int x, int y){
    for (auto panel : panels) {
        panel->mouseDragged(x, y);
    }

    float x1 = ofGetPreviousMouseX()-canvasR.getX();
    float y1 = ofGetPreviousMouseY()-canvasR.getY();
    float x2 = ofGetMouseX()-canvasR.getX();
    float y2 = ofGetMouseY()-canvasR.getY();
    
    if (x2 < 0 || x2 > canvasR.getWidth() || y2 < 0 || y2 > canvasR.getHeight()) {
        return;
    }
    
    changed = true;
    toSavePrev = true;
    
    canvas.begin();
    
    ofSetColor(currentColor);
    
    if (isLine) {
        float lw = ofLerp(minWidth, maxWidth, value);
        ofSetLineWidth(lw);
        ofNoFill();
        ofDrawLine(x1, y1, x2, y2);
    }
    else {
        ofFill();
        float rad = ofLerp(minWidth, maxWidth, value);
        ofDrawEllipse(x2, y2, rad, rad);
    }
    
    canvas.end();
}

//--------------------------------------------------------------
void ofxCanvas::mousePressed(int x, int y){
    for (auto panel : panels) {
        panel->mousePressed(x, y);
    }
}


//--------------------------------------------------------------
void ofxCanvas::mouseReleased(int x, int y){
    for (auto panel : panels) {
        panel->mouseReleased(x, y);
    }
    
    update();
    toClassify = true;
    points.clear();
    
    if (toSavePrev) {
        toSavePrev = false;
        savePrevious();
    }
}

