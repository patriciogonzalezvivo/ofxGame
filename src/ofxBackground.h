/*
 *  ofxBackground.h
 *  pakapakaCorto
 *
 *  Created by Patricio González Vivo on 30/06/11.
 *  Copyright 2011 PatricioGonzalezVivo.com. All rights reserved.
 *
 */

#ifndef OFXBACK
#define OFXBACK

#include "ofxObject.h"

class ofxBackground : public ofxGameObj {
public:
	ofxBackground(){
		objectName = "background"; 
		loadXml();
		image.allocate(width, height, OF_IMAGE_COLOR);
		image.loadImage(file);
		width	= image.getWidth();
		height	= image.getHeight();
		saveXml();
	};
	
	void	draw(){ draw(x,y);};
	void	draw(int _x, int _y){
		ofPushMatrix();
		ofTranslate(_x - width*0.5, _y - height*0.5);
		ofScale(scale, scale);
		image.draw(0,0);
		
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
	};
	
private:
	ofImage		image;
};
#endif