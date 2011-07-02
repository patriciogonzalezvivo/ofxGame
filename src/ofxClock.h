/*
 *  ofxClock.h
 *  Pakapaka
 *
 *  Created by Patricio González Vivo on 25/06/11.
 *  Copyright 2011 PatricioGonzalezVivo.com. All rights reserved.
 *
 */

#ifndef OFXCLOCK
#define OFXCLOCK

#include "ofxObject.h"

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
	
	void	setFps(float _fps = 30){fps = _fps;};	// default 30fps 
	
	void	start(int _seconds){timer = _seconds*fps;};
	void	stop(){timer -1;};
	
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
			ofTranslate(_x ,_y);
			ofScale(scale, scale);
			font.drawString(time,-width*0.5,-height*0.5);
			
			if (*bDebug){
				ofSetColor(255, 100);
				ofLine(0,0, 0, height);
				ofLine(0,0, width, 0);
				ofLine(width,0, 0, 0);
				ofLine(0,height, 0, 0);
				ofLine(0,height,width,height);
				ofLine(0, 0, width, height);
				ofLine(width,0,0,height);
				ofSetColor(255, 255);
			}
			
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