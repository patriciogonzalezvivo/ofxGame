/*
 *  ofxGameCamera.h
 *
 *  Created by Patricio González Vivo on 05/07/11.
 *  Copyright 2011 PatricioGonzalezVivo.com. All rights reserved.
 *
 */

#ifndef OFXGAMECAM
#define OFXGAMECAM

#include "ofMain.h"
#include "ofxGameObj.h"

class ofxGameCam{
public:
	ofxGameCam(){
		bFixed = false;
		bVertical = false; 
		bHorizontal = true;
	};
	
	ofxGameCam& setTarget(ofxGameObj * _target){target = _target; return * this; };
	ofxGameCam& setArea(ofxGameObj * _area){target = _area; return * this; };
	
	ofxGameCam& apply(){
		if (!bFixed){
			width = ofGetWindowSize().x;
			height = ofGetWindowSize().y;
		}
		
		if (bHorizontal){
			float center = width * 0.5;
			if (target->getPosition().x > area->getScaledWidth() - center)
				ofTranslate(-area->getScaledWidth() + width, 0);	
			else if (target->getPosition().x > center)
				ofTranslate(center - target->getPosition().x, 0);
		}
		
		if (bVertical){
			/*
			 * TODO
			 */
		}
	};
	
	int		getWidth(){return width;};
	int		getHeight(){return height;};
	
	bool	isOver(ofPoint _loc){return isOver(_loc.x, _loc.y);};
	bool	isOver(float _x, float _y);
	
protected:	
	ofxGameObj* target;
	ofxGameObj* area;
	
	int			x,y,width, height;
	bool		bFixed, bVertical, bHorizontal;
};
#endif