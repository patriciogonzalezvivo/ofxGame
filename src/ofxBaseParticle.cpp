#include "ofxBaseParticle.h"

ofxBaseParticle::ofxBaseParticle(){
	image = NULL;
    position.set(0, 0);
	movement.set(0, 0);
	
	color.set(255);
	
	alphaF = 1;
	scaleF = 1;
	friction = 0.98;
	
	size = originalSize = 5;
	collisionDamp = 2;
	
	scale = 1;
	alpha = 255;
	
	life = -1;
	intUserData = -1;
	time = 0;
	
	free = true;
	live = true;
	fixed = false;
}

ofxBaseParticle::~ofxBaseParticle(){
	
}

ofxBaseParticle& ofxBaseParticle::setup(ofPoint p, ofPoint m, float _size, int _life){	
    position = p;
    originalPosition = p;
    movement = m;
    size = originalSize = _size;
	
	return * this;
}

void ofxBaseParticle::baseUpdate(){
	if (life != -1 && ofGetElapsedTimeMillis() - time > life) 
		kill();
	else 
		update();
}

float ofxBaseParticle::getDirection(){
    return sqrt(movement.x * movement.x + movement.y * movement.y);
}

float ofxBaseParticle::getLife(){
	return ofClamp((ofGetElapsedTimeMillis() - time) / (float)life, 0, 1);
}

void ofxBaseParticle::collide(ofxBaseParticle * p){
    if (p != this){
        float dst = (size + p->size);

        if (fabsf(position.x - p->position.x) < dst && fabsf(position.y - p->position.y) < dst){
            float d = ofDist(position.x, position.y, p->position.x, p->position.y);
            if (d < dst){
                float dx = (p->position.x - position.x) / d;
                float dy = (p->position.y - position.y) / d;

                movement.x += dx * (d - dst) / collisionDamp;
                movement.y += dy * (d - dst) / collisionDamp;

                p->movement.x -= dx * (d - dst) / collisionDamp;
                p->movement.y -= dy * (d - dst) / collisionDamp;

				collisionEvent();
            }
        }
    }
}

void ofxBaseParticle::moveTo(ofPoint tp, float motionDamp){
    movement.x += (tp.x - position.x) / motionDamp;
    movement.y += (tp.y - position.y) / motionDamp;
}

void ofxBaseParticle::moveAway(ofPoint tp, float dist, float motionDamp){
    float dx = (tp.x - position.x);
    float dy = (tp.y - position.y);

    if (fabsf(dx) < dist && fabsf(dy) < dist){
        float d = ofDist(position.x, position.y, tp.x, tp.y);

        if (d > 0 && d < dist){
            dx /= d;
            dy /= d;

            float dd = (dist - d) / motionDamp;

            movement.x -= dx * dd;
            movement.y -= dy * dd;
        }
    }
}
