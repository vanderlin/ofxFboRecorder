//
//  ofxFboRecorder.h
//  color trail particles
//
//  Created by Todd Vanderlin on 5/22/19.
//
//

#pragma once
#include "ofMain.h"


class ofxFboRecorder {

public:
    
    class ThreadedFrame : public ofImage, public ofThread {
    public:
        bool didGetPixels = false;
        bool bDidSave = false;
        string filename;
        ThreadedFrame(ofFbo &fbo, string filename);
        ~ThreadedFrame();
        bool didSave();
        void threadedFunction();
    };
    
    
    ofxFboRecorder(float secondsToSave = 60, int fps = 60, bool bVerbose = false);
    ~ofxFboRecorder();
    
    void addFrame(ofFbo &fbo, string prefix = "frame_");
    void setRecordTime(float seconds);
    
    void setFps(int fps);
    void stop();
    void start();
    void resetCount();
    bool isRecording();
    bool isDoneSavingFrames();
    void toggleRecording();
    float getPercentCompleted();
    string getRecordingInfo();
     
private:
    
    bool bVerbose = false;
    bool bRecord = false;
    int frameCount = 0;
    int fps;
    int totalFramesToSave, totalSaved;
    vector <shared_ptr<ThreadedFrame>> frames;
    void update(ofEventArgs &e);

};
