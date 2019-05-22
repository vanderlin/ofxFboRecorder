//
//  ofxFboRecorder.cpp
//  color trail particles
//
//  Created by Todd Vanderlin on 5/22/19.
//
//

#include "ofxFboRecorder.h"


ofxFboRecorder::ofxFboRecorder(float secondsToSave, int fps, bool bVerbose) {
    this->bRecord = false;
    this->frameCount = 0;
    this->fps = fps;
    this->totalSaved = 0;
    this->totalFramesToSave = fps * secondsToSave;
    this->bVerbose = bVerbose;
    ofAddListener(ofEvents().update, this, &ofxFboRecorder::update);

}

//--------------------------------------------------------------
ofxFboRecorder::~ofxFboRecorder() {
    ofRemoveListener(ofEvents().update, this, &ofxFboRecorder::update);
}

//--------------------------------------------------------------
void ofxFboRecorder::addFrame(ofFbo &fbo, string prefix) {
    
    if (frameCount >= totalFramesToSave) {
        return;
    }
    
    string filename = prefix+ofToString(frameCount)+".png";
    
    auto frame = make_shared<ThreadedFrame>(fbo, filename);
    
    frames.push_back(frame);
    
    frameCount ++;
}

//--------------------------------------------------------------
void ofxFboRecorder::setRecordTime(float seconds) {
    totalFramesToSave = fps * seconds;
}

//--------------------------------------------------------------
void ofxFboRecorder::setFps(int fps) {
    this->fps = fps;
}

//--------------------------------------------------------------
bool ofxFboRecorder::isRecording() {
    return bRecord;
}

//--------------------------------------------------------------
void ofxFboRecorder::start() {
    bRecord = true;
}

//--------------------------------------------------------------
void ofxFboRecorder::stop() {
    bRecord = false;
}

//--------------------------------------------------------------
bool ofxFboRecorder::isDoneSavingFrames() {
    return totalSaved >= totalFramesToSave;
}

//--------------------------------------------------------------
void ofxFboRecorder::toggleRecording() {
    bRecord = !!bRecord;
    if (bRecord) start();
    else stop();
}

//--------------------------------------------------------------
void ofxFboRecorder::update(ofEventArgs &e) {
    if (bRecord) {
        auto i = frames.begin();
        while (i != frames.end()) {
            auto frame = i->get();
            if (frame->didSave()) {
                frames.erase(i);
                totalSaved ++;
            }
            else {
                i++;
            }
        }
        
        if (bRecord && isDoneSavingFrames()){
            bRecord = false;
        }
    }
}

//--------------------------------------------------------------
string ofxFboRecorder::getRecordingInfo() {
    string info = "";
    
    if(bRecord) info += "[*] Recording\n";
    info += "Total frames to save "+ofToString(totalFramesToSave) + "\n";
    info += "Current frame count " + ofToString(frameCount) + "\n";
    info += "Total frames saved " + ofToString(totalSaved) + "\n";
    if(bRecord) info += "Done saving frames " + ofToString(isDoneSavingFrames()) + "\n";
    return info;
}


//--------------------------------------------------------------
ofxFboRecorder::ThreadedFrame::ThreadedFrame(ofFbo &fbo, string filename) {
    this->filename = filename;
    setUseTexture(false);
    fbo.readToPixels(this->getPixels());
    didGetPixels = true;
    startThread();
}
ofxFboRecorder::ThreadedFrame::~ThreadedFrame() {
    stopThread();
    waitForThread(true);
}
bool ofxFboRecorder::ThreadedFrame::didSave() {
    return bDidSave;
}
void ofxFboRecorder::ThreadedFrame::threadedFunction() {
    if (!bDidSave) {
        if(didGetPixels && save(filename)) {
            bDidSave = true;
            stopThread();
            ofLog(OF_LOG_VERBOSE, "done saving " + filename);
        }
    }
}
