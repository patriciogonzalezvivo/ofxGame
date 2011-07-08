/*
 *  ofxBaseParticleEmitter.h
 *
 *  Created by Patricio González Vivo on 03/07/11.
 *  Copyright 2011 PatricioGonzalezVivo.com. All rights reserved.
 *
 */

#ifndef OFXBASEPARTICLEEMITTER
#define OFXBASEPARTICLEEMITTER

#include "ofxGameObj.h"
#include "ofxBaseParticle.h"
#include "ofxBaseParticleForce.h"
#include "ofxBaseParticleSpring.h"

#define MASKINTERACTION
#ifdef MASKINTERACTION
#include "ofxMask.h"
#endif

enum {
    PARTICLE_BORDER_DIE,
    PARTICLE_BORDER_BOUNCE,
    PARTICLE_BORDER_JUMP_TO_OPPOSITE
};

class ofxBaseParticleEmitter : public ofxGameObj {
public:
	ofxBaseParticleEmitter();
	ofxBaseParticleEmitter(string _objectName);
	~ofxBaseParticleEmitter(){clear();};
	
	ofxBaseParticleEmitter& setBoundingBox(ofxGameObj * _bbox){hasBbox = true; bbox = _bbox;return * this;};
	ofxBaseParticleEmitter& setBorderEvent(int BORDER_EVENT){borderEvent = BORDER_EVENT;return * this;};

	void addDefault();
	void addDefault(ofxBaseParticle * particle);
	void add(ofxBaseParticle * particle){particles.push_back(particle);};
	void add(ofxBaseParticleForce * force){forces.push_back(force);};
	void add(ofxBaseParticleSpring * spring){ springs.push_back(spring);};
	
	void update();
	void draw();
	void clear();
	
	void borders();
	void collision();
	
	ofxBaseParticle * getParticle(float p);
	ofxBaseParticle * getParticleAt(int n);
	
	int getNumOfParticles(){return particles.size();};
	
	void clampVelocity(ofxBaseParticle * p);
	void deleteSpring(ofxBaseParticle * p);
	#ifdef MASKINTERACTION
	void pixelCollision(ofxMask * _mask, float _force);
	#endif
protected:
	void loadExtraXml(string _file = "config.xml");
	#ifdef MASKINTERACTION
	int imageCollision(ofPoint p, float radius, float _force, unsigned char * pixels, int _width, int _height, ofPoint & _bounce);
	#endif
	
	vector<ofxBaseParticle*> particles;
	vector<ofxBaseParticleForce*> forces;
	vector<ofxBaseParticleSpring*> springs;
	
	ofxGameObj * bbox;
	
	ofImage	pImage;
	
	ofPoint initForce;
	float	maxVelocity, colDamp, sizeMax, sizeMin;
	int		borderEvent, iteration, life;
	bool	hasBbox, hasCollision, hasImage;
};
#endif