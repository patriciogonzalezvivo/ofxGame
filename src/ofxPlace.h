/*
 *  ofxPlace.h
 *  jaboneria
 *
 *  Created by Patricio González Vivo on 04/07/11.
 *  Copyright 2011 PatricioGonzalezVivo.com. All rights reserved.
 *
 */

#ifndef OFXPLACE
#define OFXPLACE

#include "ofxGameObj.h"
class ofxPlace : public ofxGameObj {
public:
	ofxPlace(string _objectName){ 
		objectName = _objectName;
		loadXml();
	};
	
	void	draw(){ draw(x,y);};
	void	draw(int _x, int _y){
			ofPushMatrix();
			ofTranslate(_x-getScaledWidth()*0.5,_y-getScaledHeight()*0.5);
			ofScale(scale, scale);
		
			if (*bDebug)
				drawBoundingBox();
			
			ofPopMatrix();
	};
};
#endif