/*
 *  ofxParticleEmitter.h
 *
 *  Created by Patricio González Vivo on 03/07/11.
 *  Copyright 2011 PatricioGonzalezVivo.com. All rights reserved.
 *
 *
 *  This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0 
 *	Unported License. To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/3.0/ 
 *	or send a letter to Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
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
	void addParticle(ofVec2f _loc, ofVec2f _vel){ addParticle(_loc,_vel,ofRandom(life),ofRandom(scale));};
	void addParticle(ofVec2f _loc, ofVec2f _vel, int _life, float _scale);
	
protected:
	void loadExtraXml(string filePath = "config.xml" );
	
	vector<ofxParticle>	particles;
	
	ofVec2f	initForce;
	ofImage	pImage;
	
	int		life,fade, melt; 
	float	randomMax,randomMin,noiseAngle,noiseTurbulence,den,spe;
	bool	noise, density;
};
#endif