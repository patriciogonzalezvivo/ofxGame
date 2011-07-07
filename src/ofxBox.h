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
	
	ofxBox& load(string _objName);
	ofxBox& loadToWorld(ofxGameEng * _gameEng, ofPoint _pos);
	
	ofxBox& setScale(float _scale){scale = _scale; return * this;};
	ofxBox& setAngle(float _angle){ angle = _angle; return * this;};
	ofxBox& setDebug(bool * _bDebug){ bDebug = _bDebug; return * this;};
	ofxBox& setOrientation(string _orientation);
	
	ofxBox& rotate(float _angle){ angle += _angle; return * this;};
	ofxBox& resize(float _resize){ scale *= _resize; return * this;};
	
	void draw(int _level = -1);
	
	bool isOver(ofVec2f _loc);
	bool isOver(int _x, int _y){ isOver(ofVec2f(_x,_y)); };
	
	ofVec2f		pos,vel;
	
protected:
	void loadParts(const string& path);
	
	vector<ofxElement> element;
	string		objDir, orientation;
	float		width, height, scale, angle, groundY;
	bool *		bDebug;
};
#endif