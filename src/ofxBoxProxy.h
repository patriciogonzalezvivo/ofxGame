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
	~ofxBoxProxy(){ clear(); };
	void clear(){ box->destroy();};
	
	ofxBoxProxy & setWorld(b2World * _b2dworld, float _groundY);

	void update(ofxParticleEmitter * _pEmit);
	void draw();
	
private:
	void loadExtraXml(string filePath = "config.xml");
	
	ofxBox*				box;			
	float				den, bou, fri,groundY;				
};
#endif
