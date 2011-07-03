/*
 *  ofxCharacter.h
 *
 *  Created by Patricio González Vivo on 23/06/11.
 *  Copyright 2011 PatricioGonzalezVivo.com. All rights reserved.
 *
 */

#ifndef OFXCHARACTER
#define OFXCHARACTER

#include "ofMain.h"
#include "ofxBox2d.h"

#include "ofxElement.h"
#include "ofxParticle.h"

class ofxCharacter : public ofxBox2dRect{	
public:
	ofxCharacter(){
		pos = ofVec2f(0,0);
		vel = ofVec2f(0,0);
		angle = 0;
		scale = 1;
		orientation = "LEFT";
		width = 40;
		height = 35;
		groundY = 0;
		worldLoaded = false;
	};
	
	ofxCharacter &	load(string _characterName){
		charDir = _characterName;
		string _path = charDir+ "/config.character";
		loadParts( _path );	
		cloud.loadImage("cloud.png");
		return * this;
	};
	
	ofxCharacter &	loadToWorld(b2World * _b2dworld, ofPoint _pos, int _groundY = 0){
		setPhysics(0.5, 0.1, 0.1);
		setup(_b2dworld,_pos.x,_pos.y,width*scale,height*scale);	
		groundY = _groundY;
		worldLoaded = true;
		return * this;
	};
	
	int	getWidth(){return width;};
	int	getHeight(){return height;};
	
	ofxCharacter &	reset(){
		setLeftArmAngle(0);
		setRightArmAngle(0);
		setLeftLegAngle(0);
		setRightLegAngle(0);
		setOrientation("LEFT");
		worldLoaded = false;
		destroy();
	};
	
	ofxCharacter &	rotate(float _angle){ angle += _angle; return * this;};
	ofxCharacter &	resize(float _resize){ scale *= _resize; return * this;};
	ofxCharacter &	setScale(float _scale){ scale = _scale; return * this;};
	ofxCharacter &	setAngle(float _angle){ angle = _angle; return * this;};
	
	ofxCharacter &	setRightLegAngle(float _angle){bPart[2].north = _angle; return * this;}
	ofxCharacter &	setLeftLegAngle(float _angle){bPart[3].north = _angle; return * this;}
	ofxCharacter &	setRightArmAngle(float _angle){bPart[1].north = _angle; return * this;}
	ofxCharacter &	setLeftArmAngle(float _angle){bPart[5].north = _angle; return * this;}
	ofxCharacter &	setOrientation(string _orientation){if (_orientation != orientation) orientation = _orientation; return * this;};
	
	void	update(){
		if (worldLoaded){
			pos = getPosition();
			vel = getVelocity();
			//angle = body->GetAngle();
			
			if ((vel.x  > 3) && (groundY - pos.y <= height+20)){
				ofxParticle p;
				p.loc = ofVec3f((int)pos.x , groundY);
				p.vel = ofVec3f(-1*ofNoise(ofGetFrameNum()/25)*ofRandom(0,20),ofNoise(ofGetFrameNum()/25)*ofRandom(0,-10));
				p.setImage(&cloud);
				p.setLife(60);
				p.scale = ofRandom(1);
				particles.push_back(p);
			}
			
			if ((vel.x < -3) && (groundY - pos.y <= height+20)){
				ofxParticle p;
				p.loc = ofVec3f((int)pos.x , groundY);
				p.vel = ofVec3f(1*ofNoise(ofGetFrameNum()/25)*ofRandom(0,20),ofNoise(ofGetFrameNum()/25)*ofRandom(0,-10));
				p.setImage(&cloud);
				p.setLife(60);
				p.scale = ofRandom(1);
				particles.push_back(p);
			}
			
			if ( ((int)getVelocity().x) < 0)
				setOrientation("RIGHT");
			else 
				setOrientation("LEFT");
		}
		
		for(int i = 0; i < particles.size(); i++){
			particles[i].update();
			particles[i].life--;
		}
		
		for(int i = 0; i < particles.size(); i++)
			if ( particles[i].life <= 0 )
				particles.erase(particles.begin()+i);
		
	};
	
	void draw(bool _bDebug=false){
		/* if ( (int) vel.x == 0 ){
		 if (groundY == 0)
		 bPart[0].draw();	// Shadow
		 else
		 bPart[0].draw(bPart[0].pos.x,groundY,ofMap(groundY-bPart[0].pos.y,0,groundY,1,0));	// DrawShadow on the floor
		 
		 bPart[1].mirror = false;
		 bPart[1].draw();	// Arm L
		 bPart[2].mirror = false;
		 bPart[2].draw();	// Leg L
		 bPart[3].mirror = true;
		 bPart[3].draw();	// Leg R
		 bPart[5].mirror = false;
		 bPart[5].draw();	// Arm R
		 bPart[6].draw();	// Front Body
		 } else */
		if (orientation == "LEFT"){
			if (groundY == 0)
				bPart[0].draw();	// Shadow
			else
				bPart[0].draw(bPart[0].pos.x,groundY,ofMap(groundY-bPart[0].pos.y,0,groundY,1,0));
				//bPart[0].draw(bPart[0].pos.x,groundY-bPart[0].getHeight()*0.5,ofMap(groundY-bPart[0].pos.y,0,groundY,1,0));
			
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
				bPart[0].draw(bPart[0].pos.x,groundY,ofMap(groundY-bPart[0].pos.y,0,groundY,1,0));	// Draw shadow on the floot
			
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
		// Efectos
		for(int i = 0; i < particles.size(); i++)
			particles[i].draw();
		
		if (_bDebug){
			ofSetColor(255,50);
			ofxBox2dRect::draw();
			ofSetColor(255,255);
			ofDrawBitmapString("Vel X: " + ofToString(vel.x), pos.x -30, pos.y-7);
			ofDrawBitmapString("Vel Y: " + ofToString(vel.y), pos.x -30, pos.y+7);
		}
	};
	
	bool isOver(int _x, int _y){ isOver(ofVec2f(_x,_y)); };
	
	bool isOver(ofVec2f _loc){
		bool over = false;
		for(int i = 0; i< bPart.size(); i++)
			if (bPart[i].isOver(_loc)){
				over = true;
			}
		return over;
	};
	
	string			orientation;
	ofVec2f			pos,vel;
	
private:
	vector<ofxElement>	bPart;
	void loadParts(const string& path){
		ifstream	fs( ofToDataPath(path).c_str());
		
		string line;
		int lineCounter = 0;
		
		cout << "- Loading box: " << path << endl;
		
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
	};
	
	vector<ofxParticle>	particles;
	
	ofImage				cloud;
	string				charDir;
	float				angle, scale, groundY;
	int					width,height;
	bool				worldLoaded;
};
#endif
