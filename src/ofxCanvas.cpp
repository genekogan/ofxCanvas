#include "ofxCanvas.h"


//--------------------------------------------------------------
ofxCanvas::ofxCanvas() {
    currentColor = ofColor::black;
    isLine = true;
    value = 0.5;
    idxP = 0;
    minWidth = 1;
    maxWidth = 5;
    maxHistory = 64;
    bgColor = ofColor(255);
    toUndo = false;
    toClear = false;
    previous.clear();
    resetMouse();
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
    toRedo = false;
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
    changed = true;
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
    if (toRedo) {
        redo();
        toRedo = false;
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
void ofxCanvas::updateCanvasFromPrevious() {
    canvas.begin();
    previous[idxP].draw(0, 0);
    canvas.end();
    changed = true;
    toClassify = true;
}

//--------------------------------------------------------------
void ofxCanvas::undo() {
    if (previous.size() < 1) {
        return;
    }
    idxP = max(0, idxP-1);
    updateCanvasFromPrevious();
}

//--------------------------------------------------------------
void ofxCanvas::redo() {
    if (idxP >= (int)previous.size()-1) {
        return;
    }
    idxP = min((int)previous.size()-1, idxP+1);
    updateCanvasFromPrevious();
}

//--------------------------------------------------------------
void ofxCanvas::savePrevious() {
    while (!previous.empty() && idxP < (previous.size()-1)) {
        previous.pop_back();
    }
    ofImage prev;
    canvas.readToPixels(prev);
    previous.push_back(prev);
    if (previous.size() > maxHistory) {
        previous.erase(previous.begin());
    }
    idxP = previous.size()-1;
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
    
    if (prevMouse.x == -1e8) {
        prevMouse.set(ofGetMouseX(), ofGetMouseY());
    }
    mouse.set(ofGetMouseX(), ofGetMouseY());
    
    float x1 = prevMouse.x - canvasR.getX();
    float y1 = prevMouse.y - canvasR.getY();
    float x2 = mouse.x - canvasR.getX();
    float y2 = mouse.y - canvasR.getY();
    
    prevMouse.set(mouse.x, mouse.y);
    
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
        
        float d2 = ofDist(x1, y1, x2, y2);
        int n = 1 + 6 * int(d2 / rad);
        
        for (int i=0; i<n; i++) {
            float x2_ = ofMap(i, 0, n-1, x1, x2);
            float y2_ = ofMap(i, 0, n-1, y1, y2);
            ofDrawEllipse(x2_, y2_, rad, rad);
        }
    }
    
    canvas.end();
}

//--------------------------------------------------------------
void ofxCanvas::mousePressed(int x, int y){
    for (auto panel : panels) {
        panel->mousePressed(x, y);
    }
    mouseDragged(x, y);
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
    
    resetMouse();
}

//--------------------------------------------------------------
void ofxCanvas::resetMouse() {
    mouse = ofVec2f(-1e8, -1e8);
    prevMouse = ofVec2f(-1e8, -1e8);
}
