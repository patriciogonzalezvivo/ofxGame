#ifndef OFXBASEPARTICLE
#define OFXBASEPARTICLE

#include "ofMain.h"

class ofxBaseParticle{
public:

	ofxBaseParticle();
	~ofxBaseParticle();
		
	ofxBaseParticle& setup(ofPoint p, ofPoint m, float size, int life = -1);
	ofxBaseParticle& setPosition(ofPoint _pos){position = _pos;originalPosition = _pos;return * this;};
	ofxBaseParticle& setMovement(ofPoint _mov){movement = _mov; return * this;};
	ofxBaseParticle& setSize(float _size){ size = originalSize = _size; return * this;};
	ofxBaseParticle& setScale(float _scale){scale = _scale; return * this;};
	ofxBaseParticle& setLife(int _num){ time = ofGetElapsedTimeMillis(); initLife = life = _num; return * this;};
	ofxBaseParticle& setImage(ofImage * _image){image = _image; return * this;};
	
	void baseUpdate();

	virtual void update(){};
	virtual void draw(){
		ofPushMatrix();
		ofTranslate(position);
		ofScale(scale*scaleF, scale*scaleF);
		ofSetColor(color,color.a*alphaF);
		
		if (image != NULL)
			image->draw(-image->width*0.5,-image->height*0.5,image->width,image->height);
		else
			ofCircle(0, 0, size);
		
		ofPopMatrix();
	};
	
	virtual void collisionEvent(){};
	virtual void otherCollisionEvent(){};
	virtual void kill(){live = false;};
	
	void collide(ofxBaseParticle * p);
	
	float getDirection();
	float getLife();

	void moveTo(ofPoint targetPoint, float movementDamp);
	void moveAway(ofPoint targetPoint, float dist, float motionDamp);

	ofImage * image;
	ofColor color;
	ofPoint position, originalPosition, movement;
	
	bool live, fixed, free;
	float size, originalSize, scale, scaleF, alphaF, friction, collisionDamp;
	int initLife, life, time, intUserData, alpha;
};

#endif
