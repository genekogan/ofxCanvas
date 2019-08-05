#include "ofxCanvasPanel.h"


//--------------------------------------------------------------
ofxCanvasPanel::ofxCanvasPanel() {
    guiIsVertical = false;
    guiWidth = 0;
    guiEnd = 5;
    buttonMargin = 5;
    drawBg = true;
}

//--------------------------------------------------------------
ofxCanvasPanel::~ofxCanvasPanel() {
    clearButtons();
}

//--------------------------------------------------------------
void ofxCanvasPanel::setup(string panelName, int x, int y, int guiWidth, int buttonMargin, bool guiIsVertical, ofxCanvas *canvas) {
    this->panelName = panelName;
    this->guiIsVertical = guiIsVertical;
    this->guiWidth = guiWidth;
    this->buttonMargin = buttonMargin;
    this->canvas = canvas;
    canvas->addPanel(this);
    
    if (guiIsVertical) {
        guiR.set(x, y, guiWidth, guiWidth);
        guiEnd = guiR.getY();
    } else {
        guiR.set(x, y, guiWidth, guiWidth);
        guiEnd = guiR.getX();
    }
    
    ofAddListener(ofxCanvasButtonEvent::events, this, &ofxCanvasPanel::buttonEvent);
    ofAddListener(ofxCanvasSliderEvent::events, this, &ofxCanvasPanel::sliderEvent);
}

//--------------------------------------------------------------
void ofxCanvasPanel::setPosition(int x, int y) {
    int x0 = guiR.getX();
    int y0 = guiR.getY();
    guiR.set(x, y, guiWidth, guiWidth);
    // update buttons
    for (auto b: buttons) {
        // todo
    }
}

//--------------------------------------------------------------
void ofxCanvasPanel::buttonEvent(ofxCanvasButtonEvent &e) {
    if (e.settings.isLine == NULL && (e.settings.color == ofColor::black)) {
        canvas->toClear = true;
    }
    else if (e.settings.isLine == NULL && e.settings.color == ofColor(0, 0, 0, 0)) {
        canvas->toUndo = true;
    }
    else if (e.settings.isLine == NULL && e.settings.color == ofColor(255, 0, 0, 0)) {
        canvas->toRedo = true;
    }
    else if (e.settings.isLine == NULL && e.settings.color == ofColor(0, 255, 0, 0)) {
        canvas->minWidth = e.settings.minWidth;
        canvas->maxWidth = e.settings.maxWidth;
        if (getPanelName() == e.settings.panelName) {
            for (auto b : buttons) {
                b->setActive(b->getName() == e.settings.name);
            }
        }
    }
    else if (e.settings.isLine == NULL && e.settings.color == ofColor(0, 0, 255, 0)) {
        ofLog() << "Misc event";
    }
    else {
        canvas->setCurrentColor(e.settings.color);
        canvas->isLine = e.settings.isLine;
        if (e.settings.minWidth != NULL) {
            canvas->minWidth = e.settings.minWidth;
            canvas->maxWidth = e.settings.maxWidth;
        }
        if (getPanelName() == e.settings.panelName) {
            for (auto b : buttons) {
                b->setActive(b->getName() == e.settings.name);
            }
        }
    }
}

//--------------------------------------------------------------
void ofxCanvasPanel::setButtonEnabled(string name, bool toEnable) {
    for (auto b : buttons) {
        if (b->getName() == name) {
            b->setEnabled(toEnable);
        }
    }
}

//--------------------------------------------------------------
void ofxCanvasPanel::sliderEvent(ofxCanvasSliderEvent &e) {
    canvas->value = e.value;
}

//--------------------------------------------------------------
void ofxCanvasPanel::draw() {
    ofPushStyle();
    ofSetColor(ofColor::black);
    if (drawBg) {
        ofDrawRectangle(guiR);
    }
    for (int i=0; i<buttons.size(); i++) {
        buttons[i]->draw();
    }
    ofPopStyle();
}

//--------------------------------------------------------------
void ofxCanvasPanel::clearButtons() {
    for (vector<ofxCanvasGuiElement*>::iterator it = buttons.begin();
         it != buttons.end(); ++it) {
        delete (*it);
    }
    buttons.clear();
}

//--------------------------------------------------------------
ofxCanvasGuiElement * ofxCanvasPanel::addDrawOption(string name, ofColor color, bool isLine, float minWidth, float maxWidth, string iconPath) {
    int bX, bY, bW, bH, bM;
    int n = buttons.size();
    if (guiIsVertical) {
        bM = 10;
        bW = guiWidth - 10;
        bH = bW;
        bX = guiR.getX() + 5;
        bY = guiEnd + (n > 0 ? buttonMargin : 5);
        guiEnd = bY + bH;
        guiR.set(guiR.getX(), guiR.getY(),
                 guiWidth, bY + bH + buttonMargin);
    } else {
        bM = 10;
        bH = guiWidth - 10;
        bW = bH;
        bX = guiEnd + (n > 0 ? buttonMargin : 5);
        bY = guiR.getY() + 5;
        guiEnd = bX + bW;
        guiR.set(guiR.getX(), guiR.getY(),
                 bX + bW + buttonMargin, guiWidth);
    }
    
    ofxCanvasSettings settings;
    settings.panelName = panelName;
    settings.name = name;
    settings.color = color;
    settings.isLine = isLine;
    settings.minWidth = minWidth;
    settings.maxWidth = maxWidth;
    
    ofxCanvasButton *button = new ofxCanvasButton();
    button->setup(name, settings, bX, bY, bW, bH, guiIsVertical);
    if (iconPath != "__NONE__") {
        button->loadIcon(iconPath);
    }
    buttons.push_back(button);
    
    return button;
}

//--------------------------------------------------------------
ofxCanvasGuiElement * ofxCanvasPanel::addShapeOption(string name, ofColor color, float minWidth, float maxWidth, string iconPath) {
    return addDrawOption(name, color, false, minWidth, maxWidth, iconPath);
}

//--------------------------------------------------------------
ofxCanvasGuiElement * ofxCanvasPanel::addLineOption(string name, ofColor color, float minWidth, float maxWidth, string iconPath) {
    return addDrawOption(name, color, true, minWidth, maxWidth, iconPath);
}

//--------------------------------------------------------------
ofxCanvasGuiElement * ofxCanvasPanel::addUndoOption(string name, string iconPath) {
    return addDrawOption(name, ofColor(0, 0, 0, 0), NULL, NULL, NULL, iconPath);
}

//--------------------------------------------------------------
ofxCanvasGuiElement * ofxCanvasPanel::addRedoOption(string name, string iconPath) {
    return addDrawOption(name, ofColor(255, 0, 0, 0), NULL, NULL, NULL, iconPath);
}

//--------------------------------------------------------------
ofxCanvasGuiElement * ofxCanvasPanel::addClearOption(string name, string iconPath) {
    return addDrawOption(name, ofColor::black, NULL, NULL, NULL, iconPath);
}

//--------------------------------------------------------------
ofxCanvasGuiElement * ofxCanvasPanel::addSlider(string name, float minValue, float maxValue) {
    int bX, bY, bW, bH, bM;
    int n = buttons.size();
    if (guiIsVertical) {
        bM = 10;
        bW = 0.75 * guiWidth - 10;
        bH = 200;
        bX = guiR.getX() + 5 + 0.125 * guiWidth;
        bY = guiEnd + (n > 0 ? buttonMargin : 5);
        guiEnd = bY + bH;
        guiR.set(guiR.getX(), guiR.getY(),
                 guiWidth, bY + bH + buttonMargin);

    } else {
        bM = 10;
        bW = 200;
        bH = 0.75 * guiWidth - 10;
        bX = guiEnd + (n > 0 ? buttonMargin : 5);
        bY = guiR.getY() + 5 + 0.125 * guiWidth;
        guiEnd = bX + bW;
        guiR.set(guiR.getX(), guiR.getY(),
                 bX + bW + buttonMargin, guiWidth);
    }
    
    ofxCanvasSettings settings;
    settings.minWidth = minValue;
    settings.maxWidth = maxValue;
    
    ofxCanvasSlider *slider = new ofxCanvasSlider();
    slider->setup(name, settings, bX, bY, bW, bH, guiIsVertical);
    buttons.push_back(slider);
    
    return slider;
}

//--------------------------------------------------------------
void ofxCanvasPanel::selectRandomOption() {
    int bIdx = int(ofRandom(buttons.size()));
    buttons[bIdx]->buttonClicked();
}

//--------------------------------------------------------------
ofxCanvasGuiElement * ofxCanvasPanel::addBrushSizeOption(string name, int value, string iconPath) {
    return addDrawOption(name, ofColor(0, 255, 0, 0), NULL, value, value, iconPath);
}

//--------------------------------------------------------------
ofxCanvasGuiElement * ofxCanvasPanel::addMiscOption(string name, string iconPath) {
    return addDrawOption(name, ofColor(0, 0, 255, 0), NULL, NULL, NULL, iconPath);
}

//--------------------------------------------------------------
void ofxCanvasPanel::mouseMoved(int x, int y){
    for (auto b : buttons) {
        b->mouseMoved(x, y);
    }
}

//--------------------------------------------------------------
void ofxCanvasPanel::mouseDragged(int x, int y){
    for (auto b : buttons) {
        b->mouseDragged(x, y);
    }
}

//--------------------------------------------------------------
void ofxCanvasPanel::mousePressed(int x, int y){
    for (auto b : buttons) {
        b->mousePressed(x, y);
    }
}

//--------------------------------------------------------------
void ofxCanvasPanel::mouseReleased(int x, int y){
    for (auto b : buttons) {
        b->mouseReleased(x, y);
    }
}
