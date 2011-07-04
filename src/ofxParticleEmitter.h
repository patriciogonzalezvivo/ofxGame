/*
 *  ofxParticleEmitter.h
 *
 *  Created by Patricio González Vivo on 03/07/11.
 *  Copyright 2011 PatricioGonzalezVivo.com. All rights reserved.
 *
 */

#ifndef OFXPARTICLEEMITTER
#define OFXPARTICLEEMITTER

#include "ofxGameObj.h"
#include "ofxParticle.h"

class ofxParticleEmitter : public ofxGameObj {
public:
	ofxParticleEmitter(string _objectName){
		objectName = _objectName;
		loadXml();
		loadExtraXml();
		pImage.loadImage(file);
	}
	
	void clear(){
		particles.clear();
	}
	
	void update(){
		for(int i = 0; i < particles.size(); i++){
			if (flocking)
				particles[i].applyFlockingForce(&globalOffset,nei,ind);
			
			if (den != 0)
				particles[i].applyViscosityForce(den);
			
			if (spe != 0)
				particles[i].update(spe);
			else
				particles[i].update();
			
			particles[i].life--;
		}
		
		for(int i = 0; i < particles.size(); i++)
			if ( particles[i].life <= 0 )
				particles.erase(particles.begin()+i);
		
		globalOffset += ofVec3f(tur/nei,tur/nei,tur/nei);
	}
	
	void draw(){ 
		ofSetColor(255, 255);
		for(int i=0; i < particles.size(); i++)
			particles[i].draw();
		
		ofPushMatrix();
		ofTranslate(x-getScaledWidth()*0.5,y-getScaledHeight()*0.5);
		ofScale(scale, scale);
		
		if (*bDebug)
			drawBoundingBox();
		
		ofPopMatrix();
	};
	
	void addParticle(){ addParticle(ofPoint(x,y));};
	
	void addParticle(ofPoint _loc){
		if ((randomMax != 1) || (randomMin != 1)){
			addParticle(ofVec3f(ofRandom(_loc.x-getScaledWidth()*0.5 ,_loc.x+getScaledWidth()*0.5),
								ofRandom(_loc.y-getScaledHeight()*0.5,_loc.y+getScaledHeight()*0.5),
								0),
						ofVec3f(initForce.x*ofNoise(ofGetFrameNum()/25)*ofRandom(randomMin,randomMax),
								initForce.y*ofNoise(ofGetFrameNum()/25)*ofRandom(randomMin,randomMax),
								0));
		} else {
			addParticle(ofVec3f(ofRandom(_loc.x-getScaledWidth()*0.5 ,_loc.x+getScaledWidth()*0.5),
								ofRandom(_loc.y-getScaledHeight()*0.5 ,_loc.y+getScaledHeight()*0.5),
								0),
						ofVec3f(initForce.x,initForce.y,0));
		}
	};
	
	void addParticle(ofVec3f _loc, ofVec3f _vel){ addParticle(_loc,_vel,ofRandom(life),ofRandom(scale));};
	
	void addParticle(ofVec3f _loc, ofVec3f _vel, int _life, float _scale){
		ofxParticle p;
		p.loc = _loc;
		p.vel = _vel;
		p.setImage(&pImage);
		p.setLife(_life);
		p.scale = _scale;
		
		particles.push_back(p);
	};
	
private:
	void loadExtraXml(string filePath = "config.xml" ){
		ofxXmlSettings XML;
		cout << "Reading " << objectName << " configuration file looking for extra parametters " << filePath;
		
		if (XML.loadFile(filePath)){
			cout << " [ OK ]" << endl;
			initForce.x = XML.getValue(objectName+":xForce",0);
			initForce.y = XML.getValue(objectName+":yForce",0);
			randomMax	= XML.getValue(objectName+":randomMax",1);
			randomMin	= XML.getValue(objectName+":randomMin",1);
			life		= XML.getValue(objectName+":life",ofGetFrameRate()); 
			den			= XML.getValue(objectName+":density",0);
			spe			= XML.getValue(objectName+":speedLimit",0);
			
			flocking	= XML.tagExists(objectName+":flocking");
			
			if (flocking){
				nei = XML.getValue(objectName+":flocking:neigbordhood",12);
				ind = XML.getValue(objectName+":flocking:independence",0.01);
				tur	= XML.getValue(objectName+":flocking:turbulence",0.09); 
			}
		} else
			cout << " [ FAIL ]" << endl;
	};
	
	ofVec3f globalOffset;
	ofVec2f	initForce;
	ofImage	pImage;
	vector<ofxParticle>	particles;
	int		life;
	float	randomMax,randomMin,nei,ind,tur,den,spe;
	bool	flocking, density;
};
#endif