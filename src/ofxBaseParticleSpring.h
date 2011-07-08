#ifndef OFXBASEPARTICLESPRING
#define OFXBASEPARTICLESPRING

#include "ofMain.h"
#include "ofxBaseParticle.h"

class ofxBaseParticleSpring{
public:
	ofxBaseParticleSpring(){ };
	
	~ofxBaseParticleSpring(){ };

	void setup(ofxBaseParticle * _p1, ofxBaseParticle * _p2, float _springDamp){
		p1 = _p1;
		p2 = _p2;
		if (p1 != NULL && p2 != NULL)
		{
			springDamp = _springDamp;
			distance = ofDist(p1->position.x, p1->position.y, p2->position.x, p2->position.y);
		}
	};
	
	void update(){
		if (p1 == NULL || p2 == NULL) return;
		
		float d = ofDist(p1->position.x, p1->position.y, p2->position.x, p2->position.y);
		
		if (d == 0) return;
		
		float dx = (p2->position.x - p1->position.x) / d;
		float dy = (p2->position.y - p1->position.y) / d;
		
		if (!p1->fixed)
		{
			p1->movement.x -= dx * (distance - d) / springDamp;
			p1->movement.y -= dy * (distance - d) / springDamp;
		}
		if (!p2->fixed)
		{
			p2->movement.x += dx * (distance - d) / springDamp;
			p2->movement.y += dy * (distance - d) / springDamp;
		}
		
	};
	
	void baseDraw(){ if (p1 != NULL && p2 != NULL) draw(); };
	virtual void draw(){};

	ofxBaseParticle * p1;
	ofxBaseParticle * p2;

	float springDamp;
	float distance;
};

#endif

