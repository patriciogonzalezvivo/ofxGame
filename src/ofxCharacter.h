/*
 *  ofxCharacter.h
 *
 *  Created by Patricio González Vivo on 23/06/11.
 *  Copyright 2011 PatricioGonzalezVivo.com. All rights reserved.
 *
 *
 *  This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0 
 *	Unported License. To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/3.0/ 
 *	or send a letter to Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
 *
 */

#ifndef OFXCHARACTER
#define OFXCHARACTER

#include "ofMain.h"
#include "ofxGameEng.h"
#include "ofxElement.h"

#include "ofxBox2d.h"

class ofxCharacter : public ofxBox2dRect{	
public:
	ofxCharacter();
	
	ofxCharacter &	load(string _characterName);
	
	ofxCharacter &	loadToWorld(ofxGameEng * _gameEng, ofPoint _pos);
	ofxCharacter &	reset();
	ofxCharacter &	rotate(float _angle){ angle += _angle; return * this;};
	ofxCharacter &	resize(float _resize){ scale *= _resize; return * this;};
	ofxCharacter &	setScale(float _scale){ scale = _scale; return * this;};
	ofxCharacter &	setAngle(float _angle){ angle = _angle; return * this;};
	
	ofxCharacter &	setRightLegAngle(float _angle){bPart[2].north = _angle; return * this;}
	ofxCharacter &	setLeftLegAngle(float _angle){bPart[3].north = _angle; return * this;}
	ofxCharacter &	setRightArmAngle(float _angle){bPart[1].north = _angle; return * this;}
	ofxCharacter &	setLeftArmAngle(float _angle){bPart[5].north = _angle; return * this;}
	ofxCharacter &	setOrientation(string _orientation);
	
	int		getWidth(){return width;};
	int		getHeight(){return height;};
	
	
	void draw(bool _bDebug);
	
	bool isOver(int _x, int _y){ isOver(ofVec2f(_x,_y)); };
	bool isOver(ofVec2f _loc);
	
	string			orientation;
	ofVec2f			pos,vel;
	
protected:
	void loadParts(const string& path);

	vector<ofxElement>	bPart;
	
	string				charDir;
	float				angle, scale, groundY;
	int					width,height;
	bool				worldLoaded;
};
#endif
