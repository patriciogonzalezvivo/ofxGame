/*
 *  ofxCharacter.cpp
 *
 *  Created by Patricio González Vivo on 04/07/11.
 *  Copyright 2011 PatricioGonzalezVivo.com. All rights reserved.
 *
 *
 *  This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0 
 *	Unported License. To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/3.0/ 
 *	or send a letter to Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
 *
 */
#include "ofxCharacter.h"

ofxCharacter::ofxCharacter(){
	pos = ofVec2f(0,0);
	vel = ofVec2f(0,0);
	angle = 0;
	scale = 1;
	orientation = "LEFT";
	width = 40;
	height = 35;
	groundY = 0;
	worldLoaded = false;
}

ofxCharacter & ofxCharacter::load(string _characterName){
	charDir = _characterName;
	string _path = charDir+ "/config.character";
	loadParts( _path );
	setPhysics(0.5, 0.1, 0.1);
	return * this;
}

ofxCharacter & ofxCharacter::loadToWorld(ofxGameEng * _gameEng, ofPoint _pos){
	setup(_gameEng->getWorld(),_pos.x,_pos.y,width*scale,height*scale);	
	groundY = _gameEng->getGround().y;
	worldLoaded = true;
	return * this;
}

ofxCharacter & ofxCharacter::reset(){
	setLeftArmAngle(0);
	setRightArmAngle(0);
	setLeftLegAngle(0);
	setRightLegAngle(0);
	setOrientation("LEFT");
	worldLoaded = false;
	destroy();
}

ofxCharacter & ofxCharacter::setOrientation(string _orientation){
	if (_orientation != orientation) {
		orientation = _orientation;
		if (worldLoaded){
			vel = getVelocity();
			addForce(ofVec2f(vel.x*-1,0), 15);
		}
	}
	return * this;
}

void ofxCharacter::draw(bool _bDebug=false){
	if (orientation == "LEFT"){
		if (groundY == 0)
			bPart[0].draw();	// Shadow
		else
			bPart[0].draw(pos.x,groundY,ofMap(groundY-pos.y,height,groundY-height,1,0));
		
		bPart[1].mirror = false;
		bPart[1].draw();	// Arm L
		bPart[2].mirror = false;
		bPart[2].draw();	// Leg L
		bPart[3].mirror = false;
		bPart[3].draw();	// Leg R
		bPart[4].mirror = false;
		bPart[4].draw();	// Body not fliped
		bPart[5].mirror = false;
		bPart[5].draw();	// Arm R
	} else if (orientation == "RIGHT") {
		if (groundY == 0)
			bPart[0].draw();	// Shadow
		else
			bPart[0].draw(pos.x,groundY,ofMap(groundY-pos.y,height,groundY-height,1,0));
		
		bPart[5].mirror = true;
		bPart[5].draw();	// Arm R
		bPart[2].mirror = true;
		bPart[2].draw();	// Leg L
		bPart[3].mirror = true;
		bPart[3].draw();	// Leg R
		bPart[4].mirror = true;
		bPart[4].draw();	// Body fliped
		bPart[1].mirror = true;
		bPart[1].draw();	// Arm L
	}
	
	if (_bDebug){
		ofSetColor(255,50);
		ofxBox2dRect::draw();
		ofSetColor(255,255);
		ofDrawBitmapString("Vel X: " + ofToString(vel.x), pos.x -30, pos.y-7);
		ofDrawBitmapString("Vel Y: " + ofToString(vel.y), pos.x -30, pos.y+7);
	}
}

bool ofxCharacter::isOver(ofVec2f _loc){
	bool over = false;
	for(int i = 0; i< bPart.size(); i++)
		if (bPart[i].isOver(_loc)){
			over = true;
		}
	return over;
}

void ofxCharacter::loadParts(const string& path){
	ifstream	fs( ofToDataPath(path).c_str());
	
	string line;
	int lineCounter = 0;
	
	//cout << "- Loading box: " << path << endl;
	
	while(!(fs >> line).fail()){
		vector <string> values = ofSplitString(line, ",");
		
		string _pathImage = values[0];
		float _radio = ofToFloat(values[1].c_str());             // the first value is the Letter or Key, the second one is radio from the center
		float _angle = ofToFloat(values[2].c_str());				// the 3th is the angle on radians from the center (this last to parameters are the ones that let the keabord be redraw in any angle and continue working)
		int	_xI	= ofToInt(values[3].c_str());               // the 4th and 5th are the with and height of each key. 
		int	_yI	= ofToInt(values[4].c_str());
		bool _m = ( ofToInt(values[5].c_str() ) != 0 )?true:false;
		
		_pathImage = charDir + "/" + _pathImage;
		ofxElement p = ofxElement( _pathImage,_radio, _angle, _xI, _yI,_m);
		
		if (_pathImage == (charDir + "/shadow.png")){
			height = p.getRadio();
			width = height;
		}
		
		p.setScale(&scale);
		p.setBodyNorth(&angle);
		p.setBodyCenter(&pos);
		p.fromPolarToCart();
		
		bPart.push_back(p);
	}
	
	fs.seekg(0,ios::beg);
	fs.clear();
	fs.close();
}