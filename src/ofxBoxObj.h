/*
 *  ofxBoxObj.h
 *
 *  Created by Patricio González Vivo on 02/07/11.
 *  Copyright 2011 PatricioGonzalezVivo.com. All rights reserved.
 *
 */

#ifndef OFXBOXPROXY
#define OFXBOXPROXY

#include "ofxBox.h"
#include "ofxGameObj.h"
#include "ofxGameEng.h"

#include "ofxParticleEmitter.h"

class ofxBoxObj : public ofxGameObj {
public:
	ofxBoxObj(string _objectName);
	~ofxBoxObj(){ box->destroy(); };
	
	ofxBoxObj& setEngine(ofxGameEng * _gameEng){ gameEng = _gameEng;return * this;};
	ofxBoxObj& init(){init(x,y);return * this;};
	ofxBoxObj& init(int _x, int _y);
	ofxBoxObj& restart();
	
	void update(ofxParticleEmitter * _pEmit);
	void draw(int _level = -1);
	
protected:
	void		loadExtraXml(string filePath = "config.xml");
	ofxGameEng* gameEng;
	ofxBox*		box;
	b2World *	b2dworld;
	float		den, bou, fri,groundY;				
};
#endif
