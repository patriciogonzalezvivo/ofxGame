/*
 *  ofxPlace.h
 *
 *  Created by Patricio González Vivo on 04/07/11.
 *  Copyright 2011 PatricioGonzalezVivo.com. All rights reserved.
 *
 *
 *  This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0 
 *	Unported License. To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/3.0/ 
 *	or send a letter to Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
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