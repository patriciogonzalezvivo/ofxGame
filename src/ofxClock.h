/*
 *  ofxClock.h
 *
 *  Created by Patricio González Vivo on 25/06/11.
 *  Copyright 2011 PatricioGonzalezVivo.com. All rights reserved.
 *
 *
 *  This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0 
 *	Unported License. To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/3.0/ 
 *	or send a letter to Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
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
		playing = false;
		saveXml();
	};
	
	ofxClock& setFps(float _fps = 30){fps = _fps;return * this;};	// default 30fps 
	
	ofxClock& start(int _seconds){timer = _seconds*fps; playing = true;return * this;};
	ofxClock& pause(){playing = false; return * this;};
	ofxClock& stop(){playing = false; timer = -1;return * this;};
	
	bool	isPlaying(){return playing;};
	bool	isDone(){return (timer == -1)?true:false;};
	int		getSeconds(){return timer/fps;};
	
	void	update(){ if ((timer >= 0)){ if (playing) timer--; } else stop(); };
	void	draw(){ draw(x,y);};
	void	draw(int _x, int _y){
		if ((timer != -1)) {
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
	
protected:
	string nf(string format, int number) {
		char buffer[100];
		sprintf(buffer, format.c_str(), number);
		return (string)buffer;
	}
	
	ofTrueTypeFont		font;
	int		fps,timer;
	bool	playing;
};
#endif