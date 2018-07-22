#include "ofxCanvas.h"


//--------------------------------------------------------------
ofxCanvas::ofxCanvas() {
    currentColor = ofColor::black;
    isLine = true;
    value = 0.5;
    minWidth = 1;
    maxWidth = 5;
    guiIsVertical = false;
    guiEnd = 0;
}

//--------------------------------------------------------------
ofxCanvas::~ofxCanvas() {
    clearButtons();
}

//--------------------------------------------------------------
void ofxCanvas::clearButtons() {
    for (vector<ofxCanvasGuiElement*>::iterator it = buttons.begin();
         it != buttons.end(); ++it) {
        delete (*it);
    }
    buttons.clear();
}

//--------------------------------------------------------------
void ofxCanvas::setup(int x, int y, int width, int height, int guiWidth, bool guiIsVertical) {
    this->guiIsVertical = guiIsVertical;
    this->guiWidth = guiWidth;
    if (guiIsVertical) {
        guiR.set(x, y, guiWidth, height);
        canvasR.set(x + guiWidth + 20, y, width, height);
        guiEnd = guiR.getY();
    } else {
        guiR.set(x, y, width, guiWidth);
        canvasR.set(x, y + guiWidth + 20, width, height);
        guiEnd = guiR.getX();
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
    ofAddListener(ofxCanvasSliderEvent::events, this, &ofxCanvas::sliderEvent);
}

//--------------------------------------------------------------
void ofxCanvas::addDrawOption(string msg, ofColor color, bool isLine, float minWidth, float maxWidth) {
    int bX, bY, bW, bH, bM;
    int n = buttons.size();
    if (guiIsVertical) {
        bM = 10;
        bW = guiWidth - 10;
        bH = 75;
        bX = guiR.getX() + 5;
        bY = guiEnd + 5;
        guiEnd = bY + bH;
    } else {
        bM = 10;
        bW = 120;
        bH = guiWidth - 10;
        bX = guiEnd + 5;
        bY = guiR.getY() + 5;
        guiEnd = bX + bW;
    }
    
    ofxCanvasSettings settings;
    settings.color = color;
    settings.isLine = isLine;
    settings.minWidth = minWidth;
    settings.maxWidth = maxWidth;
    
    ofxCanvasButton *button = new ofxCanvasButton();
    button->setup(msg, settings, bX, bY, bW, bH, guiIsVertical);
    buttons.push_back(button);
}

//--------------------------------------------------------------
void ofxCanvas::addShapeOption(string msg, ofColor color, float minWidth, float maxWidth) {
    addDrawOption(msg, color, false, minWidth, maxWidth);
}

//--------------------------------------------------------------
void ofxCanvas::addLineOption(string msg, ofColor color, float minWidth, float maxWidth) {
    addDrawOption(msg, color, true, minWidth, maxWidth);
}

//--------------------------------------------------------------
void ofxCanvas::addUndoOption(string msg) {
    addDrawOption(msg, NULL, NULL, NULL, NULL);
}

//--------------------------------------------------------------
void ofxCanvas::addSlider(string msg, float minValue, float maxValue) {
    int bX, bY, bW, bH, bM;
    int n = buttons.size();
    if (guiIsVertical) {
        bM = 10;
        bW = 0.75 * guiWidth - 10;
        bH = 200;
        bX = guiR.getX() + 5 + 0.125 * guiWidth;
        bY = guiEnd + 5;
        guiEnd = bY + bH;
    } else {
        bM = 10;
        bW = 200;
        bH = 0.75 * guiWidth - 10;
        bX = guiEnd + 5;
        bY = guiR.getY() + 5 + 0.125 * guiWidth;
        guiEnd = bX + bW;
    }
    
    ofxCanvasSettings settings;
    settings.minWidth = minValue;
    settings.maxWidth = maxValue;
    
    ofxCanvasSlider *slider = new ofxCanvasSlider();
    slider->setup(msg, settings, bX, bY, bW, bH, guiIsVertical);
    buttons.push_back(slider);
}

//--------------------------------------------------------------
void ofxCanvas::setCanvasPosition(int x, int y) {
    canvasR.set(x, y, canvasR.getWidth(), canvasR.getHeight());
    if (guiIsVertical) {
        guiR.set(x, y, guiWidth, canvasR.getHeight());
        canvasR.set(x + guiWidth + 20, y, canvasR.getWidth(), canvasR.getHeight());
    } else {
        canvasR.set(x, y, canvasR.getWidth(), canvasR.getHeight());
        guiR.set(x, y, guiWidth, canvasR.getHeight());
    }
}

//--------------------------------------------------------------
void ofxCanvas::setGuiPosition(int x, int y) {
    int x0 = guiR.getX();
    int y0 = guiR.getY();
    guiR.set(x, y, canvasR.getWidth(), canvasR.getHeight());
    // update buttons
    for (auto b: buttons) {
        // todo
    }
}

//--------------------------------------------------------------
void ofxCanvas::update() {
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
void ofxCanvas::buttonEvent(ofxCanvasButtonEvent &e) {
    if (e.settings.isLine == NULL && e.settings.color == NULL) {
        undo();
    } else {
        currentColor = e.settings.color;
        isLine = e.settings.isLine;
        minWidth = e.settings.minWidth;
        maxWidth = e.settings.maxWidth;
        //lineWidth = 2;//e.lineWidth;
    }
}

//--------------------------------------------------------------
void ofxCanvas::sliderEvent(ofxCanvasSliderEvent &e) {
    value = e.value;
}

//--------------------------------------------------------------
void ofxCanvas::undo() {
    cout << " INDO " << previous.size() << endl;
    if (previous.size() < 2) {
        return;
    }
    canvas.begin();
    previous[previous.size()-2].draw(0, 0);
    canvas.end();
    previous.pop_back();
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
    
    if (isLine) {
        float lw = ofLerp(minWidth, maxWidth, value);
        ofSetLineWidth(lw);
        //cout << minWidth << " " << maxWidth << " " << value << " " << lw << " ----" << endl;
        ofNoFill();
        ofDrawLine(x1, y1, x2, y2);
    }
    else {
        ofFill();
        float rad = ofLerp(minWidth, maxWidth, value);
        //cout << minWidth << " " << maxWidth << " " << value << " " << rad << " -RAD---" << endl;

        ofDrawEllipse(x2, y2, rad, rad);
    }
    
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
void ofxCanvas::savePrevious() {
    previous.resize(previous.size()+1);
    cout << "now " << previous.size() << endl;
    canvas.readToPixels(previous[previous.size()-1]);
}

//--------------------------------------------------------------
void ofxCanvas::mouseReleased(int x, int y){
    cout << "rlease" << endl;
    for (auto b : buttons) {
        b->mouseReleased(x, y);
    }

    update();
    toClassify = true;
    points.clear();
    cout << "cangd is " << changed << endl;
    
    if (changed) {
        changed = false;
        savePrevious();
    }
}
