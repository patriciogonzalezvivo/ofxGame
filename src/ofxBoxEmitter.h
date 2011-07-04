/*
 *  ofxBoxEmitter.h
 *
 *  Created by Patricio González Vivo on 02/07/11.
 *  Copyright 2011 PatricioGonzalezVivo.com. All rights reserved.
 *
 */

#ifndef OFXBOXEMITTER
#define OFXBOXEMITTER

#include "ofxGameObj.h"
#include "ofxBox.h"

class ofxBoxEmitter : public ofxGameObj {
public:
	ofxBoxEmitter(string _objectName);
	
	ofxBoxEmitter & setWorld(b2World * _b2dworld, float _groundY);
	
	void clear();
	void addBox();
	
	void draw();
	
	void loadGroup(const string& path, ofPoint _loc);
	
private:
	void loadExtraXml(string filePath = "config.xml");
	
	float				den, bou, fri, forceScale;
	ofVec2f				initForce;
	vector<ofxBox*>		boxes;
	b2World *			b2dworld;
	float				groundY;
	
};
#endif