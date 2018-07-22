#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    canvas.setup(10, 10, 800, 600, 100, false);
    //canvas.setCanvasPosition(100, 10);
    //canvas.setGuiPosition(10, 10);
    
    
    vector<int> h;
    h.push_back(1);
    h.push_back(2);
    h.push_back(3);
    h.push_back(4);
    cout << "h is " << h.size() << endl;
    cout << ofToString(h) << endl;
    h.pop_back();
    cout << "h is now " << h.size() << endl;
    cout << ofToString(h) << endl;
    
    canvas.addUndoOption("undo");
    canvas.addShapeOption("water", ofColor::blue, 10, 100);
    canvas.addShapeOption("park", ofColor::green, 10, 100);
    canvas.addShapeOption("buildings", ofColor::red, 5, 50);
    canvas.addLineOption("roads", ofColor::black, 1, 10);
    canvas.addSlider("size", 0, 1);
}

//--------------------------------------------------------------
void ofApp::update(){
}

//--------------------------------------------------------------
void ofApp::draw(){
    canvas.draw();
    canvas.drawGui();
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
