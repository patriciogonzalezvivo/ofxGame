/*
 *  ofxBoxEmitter.h
 *
 *  Created by Patricio González Vivo on 02/07/11.
 *  Copyright 2011 PatricioGonzalezVivo.com. All rights reserved.
 *
 */

#ifndef OFXBOXEMITTER
#define OFXBOXEMITTER

#include "ofxBox2d.h"

#include "ofxGameEng.h"
#include "ofxGameObj.h"

#include "ofxBox.h"

class ofxBoxEmitter : public ofxGameObj {
public:
	ofxBoxEmitter(string _objectName);
	
	ofxBoxEmitter& setEngine(ofxGameEng * _gameEng){gameEng = _gameEng;return * this;};
	void clear();
	void addBox();
	
	void draw();
	
	void loadGroup(const string& path, ofPoint _loc);
	
protected:
	void loadExtraXml(string filePath = "config.xml");
	ofxGameEng*		gameEng;
	vector<ofxBox*>	boxes;
	ofVec2f			initForce;
	float			den, bou, fri, forceScale;
};
#endif