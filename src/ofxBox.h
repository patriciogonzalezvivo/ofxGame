/*
 *  ofxPhysicBox.h
 *
 *  Created by Patricio González Vivo on 02/07/11.
 *  Copyright 2011 PatricioGonzalezVivo.com. All rights reserved.
 *
 */

#ifndef OFXPHYSICBOX
#define OFXPHYSICBOX
#include "ofxGameEng.h"
#include "ofxBox2d.h"
#include "ofxElement.h"

class ofxBox: public ofxBox2dRect {
public:
	ofxBox();
	~ofxBox(){ destroy(); };
	
	ofxBox & load(string _objName);
	ofxBox & setScale(float _scale);
	ofxBox & linkToDebug(bool * _bDebug);
	ofxBox & loadToWorld(ofxGameEng * _gameEng, ofPoint _pos);
	
	void draw(int _level = -1);
	
	bool isOver(ofVec2f _loc);
	
	ofVec2f		pos,vel;
	
private:
	void loadParts(const string& path);
	
	vector<ofxElement> element;
	string		objDir;
	float		width, height, scale, angle, groundY;
	bool *		bDebug;
};
#endif