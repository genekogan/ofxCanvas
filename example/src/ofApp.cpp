#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    canvas.setup(10, 140, 800, 600);
    //canvas.setCanvasPosition(100, 10);
    //canvas.setGuiPosition(10, 10);
    
    panel.setup("myPanel", 10, 10, 125, false, &canvas);
    panel.addClearOption("clear", "clear.png");
    panel.addUndoOption("undo", "undo.png");
    panel.addRedoOption("redo", "redo.png");
    panel.addShapeOption("water", ofColor::blue, 10, 100, "water.png");
    panel.addShapeOption("park", ofColor::green, 10, 100, "tree.png");
    panel.addShapeOption("buildings", ofColor::red, 5, 50, "house.png");
    panel.addLineOption("roads", ofColor::black, 1, 10, "road.png");
    panel.addSlider("size", 0, 1);
}

//--------------------------------------------------------------
void ofApp::update(){
}

//--------------------------------------------------------------
void ofApp::draw(){
    canvas.draw();
    panel.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    canvas.mouseMoved(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    canvas.mouseDragged(x, y);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    canvas.mousePressed(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    canvas.mouseReleased(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
