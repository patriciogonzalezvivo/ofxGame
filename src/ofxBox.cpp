/*
 *  ofxBox.cpp
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
#include "ofxBox.h"

ofxBox::ofxBox() {
	angle = 0;
	scale = 1;
	width = -1;
	height = -1;
	groundY = 0;
	
	pos = ofVec2f(0,0);
	vel = ofVec2f(0,0);
	
	orientation = "LEFT";
	bDebug = NULL;
}

ofxBox& ofxBox::load(string _objName){ 
	objDir = _objName; 
	string _path = objDir+ "/config.box"; 
	loadParts( _path );
	return * this; 
}

ofxBox& ofxBox::loadToWorld(ofxGameEng * _gameEng, ofPoint _pos) {
	setup(_gameEng->getWorld(),_pos.x,_pos.y,width*0.5*scale,height*0.5*scale);
	groundY = _gameEng->getGround().y;
	pos = getPosition();
	return * this;
}

ofxBox& ofxBox::setOrientation(string _orientation){
	if (_orientation != orientation) {
		orientation = _orientation;
		if (body != NULL){
			vel = getVelocity();
			addForce(ofVec2f(vel.x*-1,0), 15);
		}
	}
	return * this;
};

void ofxBox::draw(int _level) {
	if(body == NULL)
		return;	
	
	pos = getPosition();
	vel = getVelocity();
	angle = body->GetAngle();
	
	if ((angle >= PI-0.1) || (angle <= -PI+0.1))
		angle = 0;
	
	if (_level == -1){
		/*
		 for (int i = 0; i < bPart.size(); i++)
		 bPart[i].draw();
		 */
		if ((groundY != 0) && (groundY - (pos.y+height*0.5) < 1)){
			if ((int)vel.x == 0)
				element[1].draw(element[1].pos.x,groundY-element[1].getHeight()*0.5,ofMap(groundY-element[1].pos.y,0,groundY,1,0));	// draw Shadow on the floor
			else if (vel.x >= 1){
				element[0].mirror = false;
				element[0].draw(ofMap(vel.x,1,2,0,-1,true));
			} else if (vel.x <= -1){
				element[0].mirror = false;
				element[0].draw(ofMap(vel.x*-1,1,2,0,1,true));
			}
		}
		element[2].draw();	// draw body
		
	} else if (_level < element.size()){
		element[_level].draw();
	}
	
	if (*bDebug){
		ofSetColor(255,50);
		ofxBox2dRect::draw();
		ofSetColor(255,255);
		ofDrawBitmapString("Vel X: " + ofToString(vel.x), pos.x -30, pos.y-7);
		ofDrawBitmapString("Vel Y: " + ofToString(vel.y), pos.x -30, pos.y+7);
	}
}

bool ofxBox::isOver(ofVec2f _loc){
	bool over = false;
	
	for(int i = 0; i< element.size(); i++)
		if (element[i].isOver(_loc)){
			over = true;
		}
	
	return over;
}

void ofxBox::loadParts(const string& path){
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
		
		_pathImage = objDir + "/" + _pathImage;
		ofxElement p = ofxElement( _pathImage, _radio, _angle, _xI, _yI,_m);
		
		if (_pathImage == (objDir + "/core.png")){
			width = p.getWidth() * scale;
			height = p.getHeight() * scale;
			//cout << "--- Core Structure Found width " << width << "x" << height << endl;
		}
		
		if (_pathImage == (objDir + "/shadow.png")){
			height = p.getRadio();
		}
		
		p.setScale(&scale);
		p.setBodyNorth(&angle);
		p.setBodyCenter(&pos);
		p.fromPolarToCart();
		
		element.push_back(p);
	}
	
	fs.seekg(0,ios::beg);
	fs.clear();
	fs.close();
	
	if ((width == -1) && (height != -1))
		height = width;
}