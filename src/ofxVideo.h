/*
 *  ofxVideo.h
 *
 *  Created by Patricio González Vivo on 08/07/11.
 *  Copyright 2011 PatricioGonzalezVivo.com. All rights reserved.
 *
 *
 *  This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0 
 *	Unported License. To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/3.0/ 
 *	or send a letter to Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
 *
 */

#ifndef OFXVIDEO
#define OFXVIDEO

#include "ofxGameObj.h"

//#define	VIDEO_WITH_ALPHA			// Coment this if you don´t have ofxAlpaVideoPlayer
#ifdef VIDEO_WITH_ALPHA			
#include "ofxAlphaVideoPlayer.h"	// You can get it at: http://www.openframeworks.cc/forum/viewtopic.php?f=9&t=364&p=19620#p19620
#endif

class ofxVideo: public ofxGameObj {
public:
	ofxVideo(string _objName = "video"){
		objectName = _objName; 
		loadXml();
		video.loadMovie(file.c_str()); 
		video.setLoopState(OF_LOOP_NONE);
		width = video.width; 
		height = video.height;
		saveXml();
		objColor.set(255,0,0);
		bPlaying = false;
		video.stop();
	};
	
	ofVideoPlayer* getVideo(){ return & video;};
	
	void reload(){ 
		bPlaying = false;
		video.firstFrame();
		video.stop();
		//video.loadMovie(file.c_str()); 
	};
	void stop(){ 
		if (bPlaying){
			video.stop();
			bPlaying = false;
		}
	};
	void play(){ 
		if (!bPlaying){
			video.play();
			bPlaying = true;
		}
	};
	
	void update(){ 
		if (bPlaying){
			//video.idleMovie();
			video.update();
		}
		
		if(video.getIsMovieDone()){
			bPlaying = false;
		}
	};
	
	void draw(){ draw(x,y); };
	void draw(int _x, int _y){
		ofPushMatrix();
		ofTranslate(_x-getScaledWidth()*0.5,_y-getScaledHeight()*0.5);
		ofScale(scale, scale);
		
		ofSetColor(255, 255);
		video.draw(0, 0);
		
		if (*bDebug)
			drawBoundingBox();
		
		ofPopMatrix();
	};
	
	bool isPlaying(){ return bPlaying;};
	
protected:
#ifdef VIDEO_WITH_ALPHA
	ofxAlphaVideoPlayer video;
#else
	ofVideoPlayer	video;
#endif
	bool bPlaying;
};
#endif
