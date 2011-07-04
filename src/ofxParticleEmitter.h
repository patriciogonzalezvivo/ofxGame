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
	ofxParticleEmitter(string _objectName);
	
	void clear(){particles.clear();};
	
	void update();
	
	void draw();
	
	void addParticle(){ addParticle(ofPoint(x,y));};
	void addParticle(ofPoint _loc);
	void addParticle(ofVec3f _loc, ofVec3f _vel){ addParticle(_loc,_vel,ofRandom(life),ofRandom(scale));};
	void addParticle(ofVec3f _loc, ofVec3f _vel, int _life, float _scale);
	
private:
	void loadExtraXml(string filePath = "config.xml" );
	
	vector<ofxParticle>	particles;
	
	ofVec3f globalOffset;
	ofVec2f	initForce;
	ofImage	pImage;
	
	int		life;
	float	randomMax,randomMin,nei,ind,tur,den,spe;
	bool	flocking, density;
};
#endif