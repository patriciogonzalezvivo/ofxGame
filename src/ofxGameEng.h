/*
 *  ofxGameEng.h
 *
 *  Created by Patricio González Vivo on 05/07/11.
 *  Copyright 2011 PatricioGonzalezVivo.com. All rights reserved.
 *
 */

#ifndef OFXGAMEENG
#define OFXGAMEENG

#include "ofMain.h"
#include "ofxGameObj.h"
#include "ofxBox2d.h"

class ofxGameEng: public ofxBox2d{
public:
	ofxGameEng();

	ofxGameEng&	setBoundingObj(ofxGameObj * _boundingObj){boundingObj = _boundingObj; return * this;};
	ofxGameEng&	loadXml(string filePath);
	
	ofPoint		getGround(){return ofPoint(groundX,groundY);};
	
protected:	
	ofxGameObj* boundingObj;
	float		groundX,groundY;
};
#endif