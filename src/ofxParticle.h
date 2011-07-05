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
	ofVec2f	loc,vel,acc;
	ofVec2f	localOffset;
	ofVec2f bornVel;
	
	ofColor color;
	float	scale;
	
	float	scaleFactor;
	int		alpha;
	
	bool	bImage;
	
	ofxParticle(){
		loc.set(ofRandom(1.0f),ofRandom(1.0f));
		//loc *= ofRandom(5);
		
		vel.set(0,0);
		acc.set(0,0);
		
		localOffset.set(ofRandom(1.0f),ofRandom(1.0f));
		
		color.set(255);
		scale = 1;
		
		alpha =255;
		scaleFactor = 1;
		
		bImage = false;
	};
	
	//~ofxParticle();
	
	int		life, initLife;
	void	setLife(int _num){ initLife = life = _num; };
	
	ofImage * image;
	void	setImage(ofImage * _image){image = _image; bImage = true;};
	
	void	applyForce(ofVec2f _force){acc += _force;};
	
	void	applyViscosityForce(float _viscosity){ acc += vel.scale(_viscosity); };
	
	ofVec2f	steer(ofVec2f target, bool slowdown){
		ofVec2f steer;
		
		if (slowdown){
			ofVec3f desired = target - loc;  // A vector pointing from the location to the target
			float d = desired.length(); // Distance from the target is the magnitude of the vector
			// If the distance is greater than 0, calc steering (otherwise return zero vector)
			if (d > 0) {
				// Normalize desired
				desired.normalize();
				// Two options for desired vector magnitude (1 -- based on distance, 2 -- maxspeed)
				if (d < 1) 
					desired *= (d); // This damping is somewhat arbitrary
				//else 
				//desired *= 2;
				// Steering = Desired minus Velocity
				steer = desired - vel; //PVector.sub(desired,vel);
				//steer.limit(0.9);  // Limit to maximum steering force
			} else
				steer = ofVec3f(0,0);
			
		} else {
			steer = target -loc;
			//steer.limit(maxforce);
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
	
	void	applyArriveForce(ofVec2f target) { acc += steer(target,true); };
	void	applySeekForce(ofVec2f target) { acc += steer(target,false); };
	void	applyGravityForce(ofVec2f _center){
		ofVec2f direction = _center - loc;	// Primero calcula la dirección al centro del espacio que lo rije
		
		float d = direction.length();				// De allí calcula la fuerza con que lo atrae
		//d = constrain(d,5.0f,25.0f);
		d = ofClamp(d,5.0f,25.0f);
		
		//float force = (9.8 * space->mass * mass) / (d * d);
		float force = (9.8 * 5 * 1) / (d * d); // la masa de ambos objetos igual a 1;
		
		direction.normalize();						// Vuelve la dirección a un parámetro entre 0 y 1;
		applyForce(direction * force); 
	};
	
	void	applyNoiseForce(float _angle, float _turbulence){
		/*
		float nX = mLoc.x * 0.005f;
		float nY = mLoc.y * 0.005f;
		float nZ = app::getElapsedSeconds() * 0.1f;
		float noise = perlin.fBm( nX, nY, nZ );*/

		//float angle = ofSignedNoise(ofGetFrameNum() * 0.005f) * _angle;
		float angle = ofSignedNoise(loc.x * 0.005f, loc.y *0.005f) * _angle;
		ofVec2f noiseVector( cos( angle ), sin( angle ) );
		acc += noiseVector * _turbulence * (1.0 - ofNormalize(life, 0, initLife));
	}
	
	void applyAlpha(bool _fadeout = true){
		if (_fadeout)
			alpha = 255*(1.0f-ofNormalize(life, 0,initLife));
		else 
			alpha = 255* ofNormalize(life, 0,initLife);
	}
	
	void applyScale(bool _melt = true){
		if (_melt)
			scaleFactor = 1.0f-ofNormalize(life, 0,initLife);
		else 
			scaleFactor = ofNormalize(life, 0,initLife);
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
		ofScale(scale*scaleFactor, scale*scaleFactor, 1);
		//ofScale(scale*ofMap(life, 0,initLife, 1.5, 0.5), scale*ofMap(life, 0,initLife, 1.5, 0.5), scale);
		ofSetColor(color,alpha);
		image->draw(-image->width*0.5,-image->height*0.5,image->width,image->height);
		ofPopMatrix();
	};
	
	void	draw(float _scale){
		if (bImage){
			ofPushMatrix();
			ofTranslate(loc);
			ofScale(_scale, _scale, _scale);
			ofScale(ofMap(life, 0,initLife, 0, 1), ofMap(life, 0,initLife, 0, 1), 1);
			ofSetColor(color);
			image->draw(-image->width*0.5,-image->height*0.5,image->width,image->height);
			ofPopMatrix();
		} else {
			ofSetColor(color);
			ofCircle(loc.x, loc.y, 1);
			//draw();
		}
	};
};

#endif