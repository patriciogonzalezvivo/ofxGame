/*
 *  ofxParticle.h
 *
 *  Created by Patricio González Vivo on 24/01/11.
 *  Copyright 2011 PatricioGonzalezVivo.com. All rights reserved.
 *
 */
#ifndef _OFXPARTICLE
#define _OFXPARTICLE

#include "ofMain.h"

class ofxParticle {
public:
	ofxParticle(){
		loc.set(0,0);
		vel.set(0,0);
		acc.set(0,0);
		
		color.set(255);
		scale = 1;
		
		alphaF = 1;	// for alpha fade in/out
		scaleF = 1;	// for size fade in/out
		
		bImage = false;
		image = NULL;
	};
	
	//~ofxParticle();
	
	ofxParticle& setPosition(ofPoint _loc){ loc = _loc; return * this;};
	ofxParticle& setVelocity(ofVec2f _vel){ vel = _vel; return * this;};
	ofxParticle& setScale(float _scale){scale = _scale; return * this;};
	ofxParticle& setLife(int _num){ initLife = life = _num; return * this;};
	ofxParticle& setImage(ofImage * _image){image = _image; bImage = true; return * this;};
	
	ofxParticle& applyForce(ofVec2f _force){ acc += _force; return * this;};
	ofxParticle& applyViscosityForce(float _viscosity){ acc += vel.scale(_viscosity); return * this;};
	ofxParticle& applyArriveForce(ofVec2f target) { acc += steer(target,true); return * this;};
	ofxParticle& applySeekForce(ofVec2f target) { acc += steer(target,false); return * this;};
	ofxParticle& applyGravityForce(ofVec2f _center){
		ofVec2f direction = _center - loc;
		
		float d = direction.length();
		d = ofClamp(d,5.0f,25.0f);
		float force = (9.8 * 5 * 1) / (d * d);
		
		direction.normalize();
		applyForce(direction * force); 
		return * this;
	};
	
	ofxParticle& applyNoiseForce(float _angle, float _turbulence){
		float angle = ofSignedNoise(loc.x * 0.005f, loc.y *0.005f) * _angle;
		ofVec2f noiseVector( cos( angle ), sin( angle ) );
		acc += noiseVector * _turbulence * (1.0 - ofNormalize(life, 0, initLife));
		return * this;
	}
	
	ofxParticle& applyAlphaFade(bool _fadeout = true){
		if (_fadeout)
			alphaF = 1.0f-ofNormalize(life, 0,initLife);
		else 
			alphaF = ofNormalize(life, 0,initLife);
		return * this;
	}
	
	ofxParticle& applySizeFade(bool _melt = true){
		if (_melt)
			scaleF = 1.0f-ofNormalize(life, 0,initLife);
		else 
			scaleF = ofNormalize(life, 0,initLife);
		return * this;
	}
	
	
	void update(){
		vel += acc;
		loc += vel;
		acc *= 0;
	};
	
	void update(float _speedLimit){
		vel += acc;
		vel.limit(_speedLimit);
		loc += vel;
		acc *= 0;
	};
	
	void	draw(){
		ofPushMatrix();
		ofTranslate(loc);
		ofScale(scale*scaleF, scale*scaleF, 1);
		ofSetColor(color,color.a*alphaF);
		
		if (image != NULL)
			image->draw(-image->width*0.5,-image->height*0.5,image->width,image->height);
		else
			ofCircle(loc.x, loc.y, 1);

		ofPopMatrix();
	};
	
	int life;
	
protected:
	ofVec2f	steer(ofVec2f target, bool slowdown){
		ofVec2f steer;
		
		if (slowdown){
			ofVec3f desired = target - loc;
			float d = desired.length();
			if (d > 0) {
				desired.normalize();
				
				if (d < 1) 
					desired *= (d);
				steer = desired - vel;
			} else
				steer = ofVec3f(0,0);
			
		} else {
			steer = target -loc;
		}
		
		return steer;
	};
	
	ofVec2f	avoid(ofVec2f target, bool slowdown){
		ofVec2f steer = loc - target; 
		
		float d = steer.length();
		
		if (slowdown)
			steer *= 1/(d*d);
		
		return steer;
	};
	
	ofVec2f	loc,vel,acc;
	ofImage * image;
	ofColor color;
	float	scale, scaleF, alphaF;
	int		initLife;
	
	bool	bImage;

};

#endif