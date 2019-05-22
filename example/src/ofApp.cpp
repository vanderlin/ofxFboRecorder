#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    int fps = 60;
    int seconds = 5;
    recorder = make_shared<ofxFboRecorder>(seconds, fps);
    
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    ofSetCircleResolution(200);
    
    scale = 2;
    fbo.allocate(1920*scale, 1080*scale);
    
    recorder->start();
}

//--------------------------------------------------------------
void ofApp::update(){

    t += 0.01;
  
    
    fbo.begin();
    ofPushMatrix();
    ofTranslate(0, 0);
    ofScale(scale, scale);
    ofClear(0);
    ofBackground(0);
    int k = 1000;
    float h = (fbo.getHeight()/scale);
    for(int i=0; i<k; i++) {
        float x = i * 3;
        float y = sin(i * 0.01 + t) * (h/3);
        float r = 120 + 100 * sin((i * 0.02) + t);
        
        ofSetColor(127 + 127 * sin(i * 0.022),
                   127 + 127 * sin(i * 0.0022),
                   127 + 127 * sin(i * 0.0022));
        ofFill();
        ofDrawCircle(x, (h * 0.5) + y, r);
    }
    ofPopMatrix();
    fbo.end();
    
    if (recorder->isRecording()) {
        recorder->addFrame(fbo, "export/frame_");
    }
}

//--------------------------------------------------------------
void ofApp::draw(){

    float w = 500;
    float h = w * fbo.getHeight()/fbo.getWidth();
    ofSetColor(255);
    fbo.draw((ofGetWidth()-w)/2, (ofGetHeight()-h)/2, w, h);
    
    auto info = recorder->getRecordingInfo();
    ofDrawBitmapStringHighlight(info, 20, ofGetHeight() - 100);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == ' ') {
        recorder->toggleRecording();
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

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
