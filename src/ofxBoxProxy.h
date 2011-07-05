/*
 *  ofxBoxProxy.h
 *
 *  Created by Patricio González Vivo on 02/07/11.
 *  Copyright 2011 PatricioGonzalezVivo.com. All rights reserved.
 *
 */

#ifndef OFXBOXPROXY
#define OFXBOXPROXY

#include "ofxGameObj.h"
#include "ofxBox.h"
#include "ofxParticleEmitter.h"

class ofxBoxProxy : public ofxGameObj {
public:
	ofxBoxProxy(string _objectName);
	~ofxBoxProxy(){ box->destroy(); };
	
	ofxBoxProxy & init(int _x, int _y);
	ofxBoxProxy & restart();
	ofxBoxProxy & setWorld(b2World * _b2dworld, float _groundY){return setWorld(_b2dworld, _groundY, x, y);};
	ofxBoxProxy & setWorld(b2World * _b2dworld, float _groundY, int _x, int _y);
	
	void update(ofxParticleEmitter * _pEmit);
	void draw(int _level = -1);
	
private:
	void		loadExtraXml(string filePath = "config.xml");
	ofxBox*		box;
	b2World *	b2dworld;
	float		den, bou, fri,groundY;				
};
#endif
