/*
 *  ofxBoxObj.h
 *
 *  Created by Patricio González Vivo on 02/07/11.
 *  Copyright 2011 PatricioGonzalezVivo.com. All rights reserved.
 *
 *
 *  This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0 
 *	Unported License. To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/3.0/ 
 *	or send a letter to Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
 *
 */
#ifndef OFXBOXPROXY
#define OFXBOXPROXY

#include "ofxBox.h"
#include "ofxGameObj.h"
#include "ofxParticleEmitter.h"
#include "ofxGameEng.h"

class ofxBoxObj : public ofxGameObj {
public:
	ofxBoxObj();
	ofxBoxObj(string _objectName);
	~ofxBoxObj(){ box->destroy(); };
	
	ofxBoxObj& setEngine(ofxGameEng * _gameEng){ gameEng = _gameEng;return * this;};
	ofxBoxObj& init(){init(x,y);return * this;};
	ofxBoxObj& init(int _x, int _y);
	ofxBoxObj& restart();
	
	ofxBox*		getBox(){return box;};
	void update(ofxParticleEmitter * _pEmit);
	void draw(int _level = -1);
	
protected:
	void		loadExtraXml(string filePath = "config.xml");
	ofxGameEng* gameEng;
	ofxBox*		box;
	b2World *	b2dworld;
	string		ori;
	float		den, bou, fri,groundY;				
};
#endif
