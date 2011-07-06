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
		objColor.setHex(0x3366FF);
		loadXml();
	};
	
	void	draw(){
			ofPushMatrix();
			ofTranslate(x-getScaledWidth()*0.5,y-getScaledHeight()*0.5);
			ofScale(scale, scale);
		
			if (*bDebug)
				drawBoundingBox();
			
			ofPopMatrix();
	};
};
#endif