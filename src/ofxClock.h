/*
 *  ofxClock.h
 *
 *  Created by Patricio González Vivo on 25/06/11.
 *  Copyright 2011 PatricioGonzalezVivo.com. All rights reserved.
 *
 */

#ifndef OFXCLOCK
#define OFXCLOCK

#include "ofxGameObj.h"

class ofxClock : public ofxGameObj {
public:
	ofxClock(){ 
		fps = 30;
		objectName = "clock"; 
		loadXml();
		font.loadFont(file,14);
		width	= font.stringWidth("00:00");
		height	= font.stringHeight("00:00");
		saveXml();
	};
	
	ofxClock& setFps(float _fps = 30){fps = _fps;return * this;};	// default 30fps 
	
	ofxClock& start(int _seconds){timer = _seconds*fps;return * this;};
	ofxClock& stop(){timer -1;return * this;};
	
	bool	isDone(){return (timer == -1)?true:false;}
	
	void	update(){ if (timer >= 0) timer--; else stop(); };
	void	draw(){ draw(x,y);};
	void	draw(int _x, int _y){
		if (timer != -1) {
			int sec = timer/fps;
			int inS = (int)sec % 60;
			int inM = (( (int)sec - inS )/60)%60;
			string time = nf("%02d", inM) + ":" + nf("%02d", inS);	
			width	= font.stringWidth(time);
			height	= font.stringHeight(time);
			
			ofPushMatrix();
			ofTranslate(_x-getScaledWidth()*0.5,_y-getScaledHeight()*0.5);
			ofScale(scale, scale);
			font.drawString(time,0,0);
			
			ofTranslate(0, -height);
			if (*bDebug)
				drawBoundingBox();
			
			ofPopMatrix();
		}
	};
	
private:
	string nf(string format, int number) {
		char buffer[100];
		sprintf(buffer, format.c_str(), number);
		return (string)buffer;
	}
	
	ofTrueTypeFont		font;
	int fps,timer;
};
#endif