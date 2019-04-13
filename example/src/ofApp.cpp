#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    canvas.setup(10, 10, 800, 600, 100, false);
    //canvas.setCanvasPosition(100, 10);
    //canvas.setGuiPosition(10, 10);
    
    
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
    cout << "MM "<<x << " " << y << endl;
    canvas.mouseMoved(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    cout << "MD "<<x << " " << y << endl;
    canvas.mouseDragged(x, y);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    cout << "MP "<<x << " " << y << endl;
    canvas.mousePressed(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    cout << "MR "<<x << " " << y << endl;
    canvas.mouseReleased(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    cout << "Me "<<x << " " << y << endl;

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    cout << "Mx "<<x << " " << y << endl;

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
