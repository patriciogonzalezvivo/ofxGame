/*
 *  ofxGameEng.h
 *
 *  Created by Patricio González Vivo on 05/07/11.
 *  Copyright 2011 PatricioGonzalezVivo.com. All rights reserved.
 *
 *
 *  This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0 
 *	Unported License. To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/3.0/ 
 *	or send a letter to Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
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